#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/base/utils/Coord.h"

#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <fstream>

namespace veins {

class PandoraVehicle : public DemoBaseApplLayer {
protected:
    /* ---------- Core ---------- */
    bool hasFloatingContent;

    /* ---------- Phase 3 ---------- */
    std::map<std::string, double> sumSpeedPerRoad;
    std::map<std::string, int> speedSampleCount;

    /* ---------- Phase 4–5 ---------- */
    std::map<std::string, double> subareaSumSpeed;
    std::map<std::string, int> subareaTotalSamples;

    std::map<std::string, double> globalSumSpeed;
    std::map<std::string, int> globalTotalSamples;

    std::set<std::string> congestedRoads;
    std::set<std::pair<int, std::string>> forwardedSummaries;

    /* ---------- Zones ---------- */
    Coord criticalCenter;
    double anchorRadius;
    double forwardingRadius;

    /* ---------- Subareas ---------- */
    int kSubareas;
    double subareaCellSize;
    simtime_t subareaTxInterval;
    cMessage* subareaTimer;

    /* ---------- Phase 6: PkSP ---------- */
    int kRoutes;
    double beta;
    simtime_t rerouteCooldown;
    simtime_t lastRerouteAt;

    /* ---------- Phase 7: Metrics ---------- */
    simtime_t tripStartTime;
    simtime_t congestedTime;
    simtime_t lastSpeedSampleTime;

    int rerouteCount;
    int pandoraMsgCount;
    int vehicleId;

    static std::ofstream globalMetricsFile;
    static bool globalFileInitialized;

    double congestionThreshold;

    /* ---------- OMNeT++ ---------- */
    virtual void initialize(int stage) override;
    virtual void handleSelfMsg(cMessage* msg) override;
    virtual void handlePositionUpdate(cObject* obj) override;
    virtual void onWSM(BaseFrame1609_4* frame) override;
    virtual void finish() override;

    /* ---------- Helpers ---------- */
    bool insideAnchorZone();
    bool insideForwardingZone();

    void updateLocalRoadSpeed();
    int getSubareaId();
    double computeRoadWeightFromAvg(double avgSpeed);

    void sendSubareaSummary();
    void refreshCongestionFromGlobalAgg();

    /* ---------- Phase 6 helpers ---------- */
    std::list<std::string> getCurrentPlannedRoute();
    double routeCost(const std::list<std::string>& edges);
    int sampleBoltzmann(const std::vector<double>& costs);
    bool applyRoute(const std::list<std::string>& edges);
    void doPkspRerouteIfNeeded();
};

}
