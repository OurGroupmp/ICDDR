#include "ICDDRRSU.h"
#include "ICDDRMessage_m.h"

#include <sstream>
#include <cmath>

using namespace veins;

Define_Module(ICDDRRSU);

void ICDDRRSU::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        if (hasPar("lambda")) lambda = par("lambda").doubleValue();
        if (hasPar("cdTh")) cdTh = par("cdTh").doubleValue();
        if (hasPar("wTh")) wTh = par("wTh").doubleValue();
        if (hasPar("defaultSegLength")) defaultSegLength = par("defaultSegLength").doubleValue();
        if (hasPar("avgVehicleLen")) avgVehicleLen = par("avgVehicleLen").doubleValue();
        if (hasPar("minGap")) minGap = par("minGap").doubleValue();
    }
}

void ICDDRRSU::onWSA(DemoServiceAdvertisment* wsa) {
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void ICDDRRSU::onWSM(BaseFrame1609_4* frame) {
    // If we receive CAM, just forward it like an RSU would (V2I backbone),
    // but decrement hopsLeft so it doesn't flood infinitely.
    if (auto cam = dynamic_cast<ICDDRCAM*>(frame)) {
        if (cam->getHopsLeft() <= 0) return;
        ICDDRCAM* fwd = cam->dup();
        fwd->setHopsLeft(fwd->getHopsLeft() - 1);
        sendDown(fwd);
        return;
    }

    // If report
    if (auto rep = dynamic_cast<ICDDRSpeedReport*>(frame)) {
        processReport(rep);
        return;
    }

    DemoBaseApplLayer::onWSM(frame);
}

double ICDDRRSU::capacityFor(const std::string& /*roadId*/) const {
    // Paper: C = L / (avgVehicleLen + minGap)
    // We don't have edge length easily in this dummy; use defaultSegLength
    double denom = (avgVehicleLen + minGap);
    if (denom < 0.1) denom = 7.0;
    return defaultSegLength / denom;
}

int ICDDRRSU::ttlFromCd(double cd) const {
    // Paper’s TTL bucketing
    if (cd >= 0.7) return 4;
    if (cd > 0.4 && cd < 0.7) return 3;
    if (cd > 0.2 && cd <= 0.4) return 2;
    if (cd > 0.1 && cd <= 0.2) return 1;
    return 1;
}

void ICDDRRSU::updateVehicleCounts(long sender, const std::string& roadId) {
    auto it = lastRoadOfVehicle.find(sender);
    if (it != lastRoadOfVehicle.end()) {
        const std::string& prev = it->second;
        if (prev == roadId) return;
        // decrement old
        auto itc = segmentVehicleCount.find(prev);
        if (itc != segmentVehicleCount.end() && itc->second > 0) itc->second--;
    }
    lastRoadOfVehicle[sender] = roadId;
    segmentVehicleCount[roadId]++;
}

void ICDDRRSU::processReport(ICDDRSpeedReport* rep) {
    long sender = rep->getSenderAddress();
    std::string roadId = rep->getRoadId();

    if (roadId.empty() || roadId[0] == ':') return;

    // update vehicle counts per segment (approx density)
    updateVehicleCounts(sender, roadId);

    // aggregate alpha
    auto& a = alphaAgg[roadId];
    a.n++;
    a.sumAlpha += rep->getAlpha();

    // compute mean alpha
    double meanAlpha = a.sumAlpha / std::max(1, a.n);

    // density
    double C = capacityFor(roadId);
    double Nv = (double)segmentVehicleCount[roadId];
    double D = (C > 1e-6) ? (Nv / C) : 0.0;

    // congestion score
    double cd = lambda * (1.0 - meanAlpha) + (1.0 - lambda) * D;

    // If congested, broadcast CAM (event-driven)
    if (cd > cdTh) {
        congestedCd[roadId] = cd;
        broadcastCamIfCongested(roadId, cd);
    }
}

void ICDDRRSU::broadcastCamIfCongested(const std::string& roadId, double cd) {
    // Build CAM
    ICDDRCAM* cam = new ICDDRCAM();
    populateWSM(cam);

    // unique id
    std::ostringstream oss;
    oss << myId << "-" << roadId << "-" << camSeq++;
    cam->setCamId(oss.str().c_str());

    cam->setRoadId(roadId.c_str());
    cam->setCd(cd);
    cam->setSeqNo(camSeq);

    int ttl = ttlFromCd(cd);
    cam->setTtl(ttl);
    cam->setHopsLeft(ttl);

    // sender TPL fields: RSU doesn't move; set something stable
    // Vehicles will overwrite senderSlope/intercept when rebroadcasting anyway.
    cam->setSenderSlope(0.0);
    cam->setSenderIntercept(0.0);

    Coord p = mobility->getPositionAt(simTime());
    cam->setSenderX(p.x);
    cam->setSenderY(p.y);

    // send immediately (V2I)
    sendDown(cam);
}
