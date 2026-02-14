#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

namespace veins {

class FCRVehicle : public DemoBaseApplLayer {
protected:
    simtime_t lastMovedAt;
    bool congestionReported;

    virtual void initialize(int stage) override;
    virtual void onWSM(BaseFrame1609_4* frame) override;
    virtual void handlePositionUpdate(cObject* obj) override;
};

}
