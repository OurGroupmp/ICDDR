#include "RiderVehicle.h"
#include "RiderMessage_m.h"

using namespace veins;

Define_Module(RiderVehicle);

void RiderVehicle::initialize(int stage) {
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        riderTimer = new cMessage("riderTimer");
        scheduleAt(simTime() + uniform(1, 2), riderTimer);
    }
}

int RiderVehicle::computeCongestionFactor() {
    double speed = mobility ? mobility->getSpeed() : 0;

    if (speed < 0.1) return 10;
    if (speed < 3)   return 8;
    if (speed < 6)   return 6;
    if (speed < 9)   return 4;
    return 1;
}

int RiderVehicle::getTTLFromCongestion(int cf) {
    if (cf <= 2) return 1;
    if (cf <= 4) return 2;
    if (cf <= 7) return 3;
    return 4;
}

void RiderVehicle::proactiveDissemination(const std::string& roadId, int cf) {
    int ttl = getTTLFromCongestion(cf);

    EV << "[RIDER][PROACTIVE] Vehicle " << myId
       << " road=" << roadId
       << " CF=" << cf
       << " TTL=" << ttl
       << " time=" << simTime() << endl;
}

void RiderVehicle::reactiveRequest(const std::string& roadId) {
    EV << "[RIDER][REACTIVE] Vehicle " << myId
       << " requesting traffic info for road "
       << roadId << " at " << simTime() << endl;
}

void RiderVehicle::handleSelfMsg(cMessage* msg) {
    if (msg == riderTimer) {

        if (!mobility) {
            scheduleAt(simTime() + 10, riderTimer);
            return;
        }

        std::string roadId = mobility->getRoadId();
        if (roadId.empty() || roadId[0] == ':') {
            scheduleAt(simTime() + 10, riderTimer);
            return;
        }

        int cf = computeCongestionFactor();

        auto it = roadDatabase.find(roadId);
        if (it == roadDatabase.end() || it->second.congestionFactor != cf) {
            roadDatabase[roadId] = { cf, simTime() };
            proactiveDissemination(roadId, cf);
        }

        // Reactive logic: missing info
        if (roadDatabase.size() < 2) {
            reactiveRequest("adjacent-road");
        }

        scheduleAt(simTime() + 10, riderTimer);
    }
}
