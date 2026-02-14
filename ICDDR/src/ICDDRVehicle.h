#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "veins/modules/messages/BaseFrame1609_4_m.h"
#include "veins/base/utils/Coord.h"

#include <deque>
#include <unordered_map>

namespace veins {

class ICDDRCAM;

class ICDDRVehicle : public DemoBaseApplLayer {
protected:
    // ---- Parameters (set via omnetpp.ini) ----
    double alphaTh = 0.3;          // congestion factor threshold
    double cdTh = 0.35;            // (used at RSU; kept here for info)
    double rc = 500.0;             // comm range (m) for Dnorm
    double maxRebroadcastDelay = 0.2; // seconds (timer-backoff window)
    double minReportInterval = 1.0;   // seconds between speed reports

    // Suitability weight params
    double w1 = 0.5, w2 = 0.3, w3 = 0.2;

    // ---- State ----
    simtime_t lastReportAt;
    int currentSubscribedServiceId;

    // last positions for TPL
    std::deque<Coord> lastPos; // keep last 5

    // avg speed estimate (simple EMA / window-ish)
    double v20ema = 0.0;
    simtime_t lastSpeedUpdateAt;

    // CAM handling
    std::unordered_map<std::string, simtime_t> seenCam;            // camId -> time
    std::unordered_map<std::string, cMessage*> pendingRebroadcast; // camId -> timer

protected:
    virtual void initialize(int stage) override;
    virtual void onWSA(DemoServiceAdvertisment* wsa) override;
    virtual void onWSM(BaseFrame1609_4* frame) override;
    virtual void handleSelfMsg(cMessage* msg) override;
    virtual void handlePositionUpdate(cObject* obj) override;

    // ---- Helpers ----
    void pushPosition(const Coord& p);
    void updateAvgSpeed(double vNow);
    void computeTPL(double& slope, double& intercept) const;

    double computeRelevance(double senderSlope, double senderIntercept,
                            double senderX, double senderY) const;

    double computeSuitability(double R, double Dnorm, double cd) const;

    void maybeSendSpeedReport();
    void scheduleCamRebroadcast(ICDDRCAM* cam, double Si);
    void cancelPendingIfAny(const std::string& camId);

    void applyRerouteIfNeeded(const std::string& congestedRoadId);

    // small utility
    static double clamp(double x, double lo, double hi) {
        return x < lo ? lo : (x > hi ? hi : x);
    }
};

} // namespace veins
