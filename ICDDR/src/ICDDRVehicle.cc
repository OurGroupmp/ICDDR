#include "ICDDRVehicle.h"
#include "ICDDRMessage_m.h"

#include <cmath>
#include <sstream>

using namespace veins;

Define_Module(ICDDRVehicle);

void ICDDRVehicle::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);

    if (stage == 0) {
        currentSubscribedServiceId = -1;
        lastReportAt = SIMTIME_ZERO;
        lastSpeedUpdateAt = simTime();
        v20ema = 0.0;

        // read params if present
        if (hasPar("alphaTh")) alphaTh = par("alphaTh").doubleValue();
        if (hasPar("rc")) rc = par("rc").doubleValue();
        if (hasPar("maxRebroadcastDelay")) maxRebroadcastDelay = par("maxRebroadcastDelay").doubleValue();
        if (hasPar("minReportInterval")) minReportInterval = par("minReportInterval").doubleValue();

        if (hasPar("w1")) w1 = par("w1").doubleValue();
        if (hasPar("w2")) w2 = par("w2").doubleValue();
        if (hasPar("w3")) w3 = par("w3").doubleValue();

        // seed position buffer
        pushPosition(mobility->getPositionAt(simTime()));
    }
    if (stage == 1) {
           // mobility is safe now
           pushPosition(mobility->getPositionAt(simTime()));
       }
}

void ICDDRVehicle::onWSA(DemoServiceAdvertisment* wsa) {
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()),
                         wsa->getPsid(),
                         "ICDDR Service");
        }
    }
}

void ICDDRVehicle::onWSM(BaseFrame1609_4* frame) {
    // Could be CAM or SpeedReport (if you ever forward those)
    if (auto cam = dynamic_cast<ICDDRCAM*>(frame)) {
        std::string camId = cam->getCamId();
        // If we've seen it, drop (also cancel pending send if we somehow had one)
        if (seenCam.find(camId) != seenCam.end()) {
            cancelPendingIfAny(camId);
            return;
        }
        seenCam[camId] = simTime();

        // Visual: CAM received
        findHost()->getDisplayString().setTagArg("i", 1, "yellow");

        // Apply reroute if this congested road affects us (simple practical trigger)
        applyRerouteIfNeeded(cam->getRoadId());

        // If no hops left, stop
        if (cam->getHopsLeft() <= 0) return;

        // Compute relevance & suitability
        double R = computeRelevance(cam->getSenderSlope(), cam->getSenderIntercept(),
                                    cam->getSenderX(), cam->getSenderY());

        Coord myPos = mobility->getPositionAt(simTime());
        double dx = myPos.x - cam->getSenderX();
        double dy = myPos.y - cam->getSenderY();
        double dist = std::sqrt(dx*dx + dy*dy);
        double Dnorm = clamp(dist / rc, 0.0, 1.0);

        double Si = computeSuitability(R, Dnorm, cam->getCd());

        // distributed “best forwarder” approximation:
        // schedule rebroadcast with delay inversely proportional to Si.
        scheduleCamRebroadcast(cam, Si);
        return;
    }

    // If it's some other WSM, ignore or call base
    DemoBaseApplLayer::onWSM(frame);
}

void ICDDRVehicle::handleSelfMsg(cMessage* msg) {
    // Rebroadcast timer is named "rebroadcast:<camId>"
    std::string name = msg->getName();
    if (name.rfind("rebroadcast:", 0) == 0) {
        std::string camId = name.substr(std::string("rebroadcast:").size());

        auto it = pendingRebroadcast.find(camId);
        if (it != pendingRebroadcast.end() && it->second == msg) {
            // We stored the CAM itself inside cMessage as its "context pointer"? we didn't.
            // So instead we encoded everything in msg->par? Not available.
            // Easiest: store CAM duplicate as msg's "control info" (cObject*). We'll do that.
            auto camObj = msg->getContextPointer();
            auto cam = reinterpret_cast<ICDDRCAM*>(camObj);

            if (cam) {
                // decrement hops and send
                cam->setHopsLeft(cam->getHopsLeft() - 1);

                // update sender TPL fields to ours (so downstream can compute relevance)
                double slope=0, intercept=0;
                computeTPL(slope, intercept);
                Coord myPos = mobility->getPositionAt(simTime());
                cam->setSenderSlope(slope);
                cam->setSenderIntercept(intercept);
                cam->setSenderX(myPos.x);
                cam->setSenderY(myPos.y);

                sendDown(cam->dup());
            }

            // cleanup
            pendingRebroadcast.erase(it);
            delete cam; // we owned the duplicate stored as context
        }

        delete msg;
        return;
    }

    DemoBaseApplLayer::handleSelfMsg(msg);
}

void ICDDRVehicle::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // Update position history
    pushPosition(mobility->getPositionAt(simTime()));

    // Update avg speed estimate
    updateAvgSpeed(mobility->getSpeed());

    // Event-driven: send speed report only if alpha threshold breached
    maybeSendSpeedReport();
}

// ---------------- Helpers ----------------

void ICDDRVehicle::pushPosition(const Coord& p) {
    lastPos.push_back(p);
    while (lastPos.size() > 5) lastPos.pop_front();
}

void ICDDRVehicle::updateAvgSpeed(double vNow) {
    // EMA ~ “past ~20s” without heavy buffers
    // tau ~ 20 sec
    double dt = (simTime() - lastSpeedUpdateAt).dbl();
    if (dt <= 0) return;
    lastSpeedUpdateAt = simTime();

    double tau = 20.0;
    double a = std::exp(-dt / tau);
    v20ema = a * v20ema + (1.0 - a) * vNow;
}

void ICDDRVehicle::computeTPL(double& slope, double& intercept) const {
    // Least squares line fit y = m x + c over lastPos
    // If points are too few or vertical-ish, fallback to m=0.
    if (lastPos.size() < 2) { slope = 0; intercept = 0; return; }

    double sumX=0, sumY=0, sumXX=0, sumXY=0;
    int n = (int)lastPos.size();
    for (auto& p : lastPos) {
        sumX += p.x;
        sumY += p.y;
        sumXX += p.x * p.x;
        sumXY += p.x * p.y;
    }
    double denom = n * sumXX - sumX * sumX;
    if (std::fabs(denom) < 1e-6) {
        // nearly vertical line - approximate with huge slope
        slope = 1e6;
        intercept = lastPos.back().y - slope * lastPos.back().x;
        return;
    }
    slope = (n * sumXY - sumX * sumY) / denom;
    intercept = (sumY - slope * sumX) / n;
}

double ICDDRVehicle::computeRelevance(double senderSlope, double senderIntercept,
                                     double senderX, double senderY) const {
    // Implements Algorithm-2-ish from paper with thresholds
    // Tunables (could be params)
    double thetaT = 15.0;     // degrees
    double Ct = 50.0;         // intercept diff threshold (meters-ish)

    double Mr=0, Cr=0;
    computeTPL(Mr, Cr);

    // compute acute angle between lines:
    // theta = atan((Ms-Mr)/(1+Ms*Mr))
    double Ms = senderSlope;
    double denom = (1.0 + Ms*Mr);
    double tanVal = 0.0;
    if (std::fabs(denom) < 1e-9) tanVal = 1e9;
    else tanVal = (Ms - Mr) / denom;

    double theta = std::atan(tanVal) * (180.0 / M_PI);
    theta = std::fabs(theta);
    if (theta > 90.0) theta = 180.0 - theta;

    double dC = std::fabs(senderIntercept - Cr);

    if (theta < thetaT && dC < Ct) return 1.0;

    // Need D0 and D5 (distance from sender now vs 5th last)
    Coord cur = mobility->getPositionAt(simTime());
    Coord fifth = (lastPos.size() >= 5 ? lastPos.front() : cur);

    double D0 = std::hypot(senderX - cur.x, senderY - cur.y);
    double D5 = std::hypot(senderX - fifth.x, senderY - fifth.y);

    // Note: paper’s formula uses theta/90 scaling, but increases when theta increases.
    // That’s a bit counterintuitive; we keep it as in paper for consistency.
    double t = clamp(theta / 90.0, 0.0, 1.0);

    if (D0 < D5) {
        // moving toward sender
        return 0.5 + 0.5 * t;
    } else {
        // moving away
        return 0.5 * t;
    }
}

double ICDDRVehicle::computeSuitability(double R, double Dnorm, double cd) const {
    // Context-aware weights (Algorithm 3)
    // We'll map:
    // U = urgency ~ cd (0..1)
    // D = local density ~ 1 - (speed/freeflow approx); but we don't know freeflow reliably in vehicle.
    // We'll approximate density by low speed => higher D.
    double U = clamp(cd, 0.0, 1.0);

    double vNow = mobility->getSpeed();
    double D = 1.0 - clamp(vNow / 15.0, 0.0, 1.0); // assume 15 m/s as typical urban freeflow
    double T = 0.5; // time factor constant for now

    double rho = w1 * U + w2 * (1.0 - D) + w3 * T;
    rho = clamp(rho, 0.5, 0.9);
    double gamma = 1.0 - rho;

    double Si = rho * R + gamma * Dnorm;
    return clamp(Si, 0.0, 1.0);
}

void ICDDRVehicle::maybeSendSpeedReport() {
    // Throttle reports
    if ((simTime() - lastReportAt).dbl() < minReportInterval) return;
    if (mobility->getRoadId().empty()) return;
    if (mobility->getRoadId()[0] == ':') return; // ignore junction internal edges

    // Free-flow speed estimate:
    // Veins doesn't expose per-edge freeflow by default.
    // We'll use a stable constant (urban) and let RSU learn better if you extend it.
    double vFree = 15.0; // m/s (~54 km/h)
    double alpha = (vFree > 0.1) ? (v20ema / vFree) : 1.0;

    if (alpha > alphaTh) return;

    ICDDRSpeedReport* rep = new ICDDRSpeedReport();
    populateWSM(rep);

    rep->setSenderAddress(myId);
    rep->setRoadId(mobility->getRoadId().c_str());
    rep->setV20(v20ema);
    rep->setVFree(vFree);
    rep->setAlpha(alpha);

    Coord p = mobility->getPositionAt(simTime());
    rep->setSenderX(p.x);
    rep->setSenderY(p.y);

    sendDown(rep);
    lastReportAt = simTime();
}

void ICDDRVehicle::scheduleCamRebroadcast(ICDDRCAM* cam, double Si) {
    std::string camId = cam->getCamId();

    // If already pending, don't schedule again
    if (pendingRebroadcast.find(camId) != pendingRebroadcast.end()) return;

    // Delay: higher Si => smaller delay
    double delay = (1.0 - Si) * maxRebroadcastDelay + uniform(0.0, 0.01);

    // Make a timer message and store a duplicate CAM pointer in context
    cMessage* t = new cMessage(("rebroadcast:" + camId).c_str());
    ICDDRCAM* camCopy = cam->dup();
    t->setContextPointer(reinterpret_cast<void*>(camCopy));

    pendingRebroadcast[camId] = t;
    scheduleAt(simTime() + delay, t);
}

void ICDDRVehicle::cancelPendingIfAny(const std::string& camId) {
    auto it = pendingRebroadcast.find(camId);
    if (it == pendingRebroadcast.end()) return;

    cMessage* t = it->second;
    cancelEvent(t);

    auto camObj = t->getContextPointer();
    auto cam = reinterpret_cast<ICDDRCAM*>(camObj);
    delete cam;

    pendingRebroadcast.erase(it);
    delete t;
}

void ICDDRVehicle::applyRerouteIfNeeded(const std::string& congestedRoadId) {
    // Practical reroute trigger:
    // If we are currently on the congested edge, ask SUMO to find another route.
    // (This is how most Veins rerouting demos do it.)
    if (mobility->getRoadId() == congestedRoadId) {
        findHost()->getDisplayString().setTagArg("i", 1, "red");
        if (traciVehicle) {
            traciVehicle->changeRoute(congestedRoadId.c_str(), 9999);
        }
    }
}
