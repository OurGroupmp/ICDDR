#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include <map>
#include <string>

namespace veins {

struct RoadInfo {
    int congestionFactor;
    simtime_t lastUpdated;
};

class RiderVehicle : public DemoBaseApplLayer {
protected:
    std::map<std::string, RoadInfo> roadDatabase; // Ψ

    cMessage* riderTimer;

    virtual void initialize(int stage) override;
    virtual void handleSelfMsg(cMessage* msg) override;

    int computeCongestionFactor();
    int getTTLFromCongestion(int cf);

    void proactiveDissemination(const std::string& roadId, int cf);
    void reactiveRequest(const std::string& roadId);
};

}
