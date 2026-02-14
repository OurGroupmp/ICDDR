#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

#include <unordered_map>
#include <string>

namespace veins {

class ICDDRRSU : public DemoBaseApplLayer {
protected:
    // ---- Parameters ----
    double lambda = 0.1;       // paper uses 0.1
    double cdTh = 0.35;        // congestion decision threshold (tune)
    double wTh = 0.2;          // weight update threshold (paper)
    double defaultSegLength = 500.0; // meters (fallback)
    double avgVehicleLen = 5.0;
    double minGap = 2.0;

    // ---- State ----
    int camSeq = 0;

    // Track vehicles per road segment (very lightweight)
    std::unordered_map<long, std::string> lastRoadOfVehicle; // senderId -> roadId
    std::unordered_map<std::string, int> segmentVehicleCount; // roadId -> count

    // For congestion decision: aggregate alpha reports (simple mean)
    struct Agg {
        int n = 0;
        double sumAlpha = 0.0;
    };
    std::unordered_map<std::string, Agg> alphaAgg; // roadId -> aggregation

    // Congested set
    std::unordered_map<std::string, double> congestedCd; // roadId -> cd

protected:
    void initialize(int stage) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;

    // helpers
    double capacityFor(const std::string& roadId) const;
    int ttlFromCd(double cd) const;

    void updateVehicleCounts(long sender, const std::string& roadId);
    void processReport(class ICDDRSpeedReport* rep);
    void broadcastCamIfCongested(const std::string& roadId, double cd);
};

} // namespace veins
