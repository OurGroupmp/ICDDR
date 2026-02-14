#include "PandoraVehicle.h"
#include "PandoraMessage_m.h"

using namespace veins;

Define_Module(PandoraVehicle);

/* ---------- static definitions ---------- */
std::ofstream PandoraVehicle::globalMetricsFile;
bool PandoraVehicle::globalFileInitialized = false;

/* ================= INITIALIZE ================= */

void PandoraVehicle::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);

    if (stage == 0) {
        hasFloatingContent = false;

        criticalCenter = Coord(500, 500);
        anchorRadius = 1000;
        forwardingRadius = 1500;
        congestionThreshold = 0.5;

        kSubareas = 9;
        subareaCellSize = (2 * anchorRadius) / 3.0;
        subareaTxInterval = 1.0;

        kRoutes = 3;
        beta = 1.5;
        rerouteCooldown = 5;
        lastRerouteAt = -1;

        subareaTimer = new cMessage("subareaTimer");
        scheduleAt(simTime() + uniform(0.1, 0.3), subareaTimer);

        tripStartTime = simTime();
        congestedTime = 0;
        lastSpeedSampleTime = simTime();

        rerouteCount = 0;
        pandoraMsgCount = 0;
        vehicleId = getId();

        /* ---- open global CSV once ---- */
        if (!globalFileInitialized) {
            globalMetricsFile.open("pandora_metrics.csv");
            globalMetricsFile
                << "time,vehicleId,road,speed,isCongested,reroutes,pandoraMsgs\n";
            globalFileInitialized = true;
        }
    }
}

/* ================= SELF MSG ================= */

void PandoraVehicle::handleSelfMsg(cMessage* msg) {
    if (msg == subareaTimer) {
        sendSubareaSummary();
        scheduleAt(simTime() + subareaTxInterval, subareaTimer);
        return;
    }
    DemoBaseApplLayer::handleSelfMsg(msg);
}

/* ================= POSITION UPDATE ================= */

void PandoraVehicle::handlePositionUpdate(cObject* obj) {
    DemoBaseApplLayer::handlePositionUpdate(obj);

    updateLocalRoadSpeed();

    simtime_t now = simTime();
    if (congestedRoads.count(mobility->getRoadId()))
        congestedTime += (now - lastSpeedSampleTime);
    lastSpeedSampleTime = now;

    if (!insideForwardingZone()) {
        congestedRoads.clear();
        sumSpeedPerRoad.clear();
        speedSampleCount.clear();
        subareaSumSpeed.clear();
        subareaTotalSamples.clear();
        globalSumSpeed.clear();
        globalTotalSamples.clear();
        forwardedSummaries.clear();
        hasFloatingContent = false;
        return;
    }

    if (insideAnchorZone()) {
        refreshCongestionFromGlobalAgg();
        doPkspRerouteIfNeeded();
    }

    /* ---- global CSV logging ---- */
    globalMetricsFile
        << simTime() << ","
        << vehicleId << ","
        << mobility->getRoadId() << ","
        << mobility->getSpeed() << ","
        << (congestedRoads.count(mobility->getRoadId()) ? 1 : 0) << ","
        << rerouteCount << ","
        << pandoraMsgCount << "\n";
}

/* ================= SPEED + SUBAREA ================= */

void PandoraVehicle::updateLocalRoadSpeed() {
    std::string road = mobility->getRoadId();
    if (road.empty() || road[0] == ':') return;

    sumSpeedPerRoad[road] += mobility->getSpeed();
    speedSampleCount[road]++;
}

int PandoraVehicle::getSubareaId() {
    Coord p = mobility->getPositionAt(simTime());
    double sx = p.x - criticalCenter.x + anchorRadius;
    double sy = p.y - criticalCenter.y + anchorRadius;

    int gx = std::min(2, std::max(0, int(sx / subareaCellSize)));
    int gy = std::min(2, std::max(0, int(sy / subareaCellSize)));

    return gy * 3 + gx;
}

double PandoraVehicle::computeRoadWeightFromAvg(double avg) {
    double maxSpeed = traciVehicle->getMaxSpeed();
    if (maxSpeed <= 0) return 0;
    return 1.0 - (avg / maxSpeed);
}

/* ================= SUBAREA SUMMARY ================= */

void PandoraVehicle::sendSubareaSummary() {
    if (!(insideAnchorZone() || insideForwardingZone())) return;

    int sid = getSubareaId();

    for (auto& it : sumSpeedPerRoad) {
        int n = speedSampleCount[it.first];
        if (n <= 0) continue;

        PandoraMessage* msg = new PandoraMessage();
        populateWSM(msg);
        msg->setRoadId(it.first.c_str());
        msg->setSubareaId(sid);
        msg->setAvgSpeed(it.second / n);
        msg->setSamples(n);
        msg->setTimestamp(simTime());
        msg->setCriticalCenter(criticalCenter);
        msg->setAnchorRadius(anchorRadius);

        pandoraMsgCount++;
        sendDown(msg);
    }
}

/* ================= RECEIVE ================= */

void PandoraVehicle::onWSM(BaseFrame1609_4* frame) {
    auto* msg = dynamic_cast<PandoraMessage*>(frame);
    if (!msg) return;

    pandoraMsgCount++;

    std::string road = msg->getRoadId();
    double sum = msg->getAvgSpeed() * msg->getSamples();

    globalSumSpeed[road] += sum;
    globalTotalSamples[road] += msg->getSamples();

    if (msg->getSubareaId() == getSubareaId()) {
        subareaSumSpeed[road] += sum;
        subareaTotalSamples[road] += msg->getSamples();
        return;
    }

    auto key = std::make_pair(msg->getSubareaId(), road);
    if (!forwardedSummaries.count(key)) {
        forwardedSummaries.insert(key);
        sendDelayedDown(msg->dup(), uniform(0.05, 0.2));
    }
}

/* ================= CONGESTION ================= */

void PandoraVehicle::refreshCongestionFromGlobalAgg() {
    for (auto& it : globalSumSpeed) {
        int n = globalTotalSamples[it.first];
        if (n <= 0) continue;

        double w = computeRoadWeightFromAvg(it.second / n);
        if (w >= congestionThreshold) {
            congestedRoads.insert(it.first);
            hasFloatingContent = true;
        }
    }
}

/* ================= PkSP ================= */

std::list<std::string> PandoraVehicle::getCurrentPlannedRoute() {
    return traciVehicle->getPlannedRoadIds();
}

double PandoraVehicle::routeCost(const std::list<std::string>& edges) {
    double cost = 0;
    for (auto& e : edges) {
        if (globalTotalSamples[e] > 0)
            cost += computeRoadWeightFromAvg(globalSumSpeed[e] / globalTotalSamples[e]);
        else
            cost += 0.05;
    }
    return cost;
}

int PandoraVehicle::sampleBoltzmann(const std::vector<double>& costs) {
    double Z = 0;
    std::vector<double> w(costs.size());
    for (size_t i = 0; i < costs.size(); i++) {
        w[i] = std::exp(-beta * costs[i]);
        Z += w[i];
    }

    double r = uniform(0.0, 1.0), c = 0;
    for (size_t i = 0; i < w.size(); i++) {
        c += w[i] / Z;
        if (r <= c) return i;
    }
    return w.size() - 1;
}

bool PandoraVehicle::applyRoute(const std::list<std::string>& edges) {
    return traciVehicle->changeVehicleRoute(edges);
}

void PandoraVehicle::doPkspRerouteIfNeeded() {
    std::string cur = mobility->getRoadId();
    if (!congestedRoads.count(cur)) return;

    if (lastRerouteAt >= SIMTIME_ZERO &&
        (simTime() - lastRerouteAt) < rerouteCooldown)
        return;

    std::list<std::string> base = getCurrentPlannedRoute();
    if (base.size() < 2) return;

    std::vector<std::list<std::string>> candidates;
    std::vector<double> costs;

    for (int i = 0; i < kRoutes; i++) {
        traciVehicle->changeRoute(cur.c_str(), 9999);
        auto alt = getCurrentPlannedRoute();
        if (!alt.empty()) {
            candidates.push_back(alt);
            costs.push_back(routeCost(alt));
        }
    }

    int chosen = sampleBoltzmann(costs);
    if (applyRoute(candidates[chosen])) {
        lastRerouteAt = simTime();
        rerouteCount++;
    }

    applyRoute(base);
}

/* ================= ZONES ================= */

bool PandoraVehicle::insideAnchorZone() {
    return mobility->getPositionAt(simTime()).distance(criticalCenter) <= anchorRadius;
}

bool PandoraVehicle::insideForwardingZone() {
    return mobility->getPositionAt(simTime()).distance(criticalCenter) <= forwardingRadius;
}

/* ================= FINISH ================= */

void PandoraVehicle::finish() {
    if (vehicleId == 0 && globalMetricsFile.is_open()) {
        globalMetricsFile.flush();
        globalMetricsFile.close();
    }
}
