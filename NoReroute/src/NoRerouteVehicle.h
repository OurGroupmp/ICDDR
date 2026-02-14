#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

namespace veins{

class NoRerouteVehicle : public DemoBaseApplLayer {
protected:
    bool sentMessage;
    simtime_t lastDroveAt;
    int currentSubscribedServiceId;

    virtual void initialize(int stage) override;
    virtual void onWSA(DemoServiceAdvertisment* wsa) override;
    virtual void onWSM(BaseFrame1609_4* frame) override;
    virtual void handleSelfMsg(cMessage* msg) override;
    virtual void handlePositionUpdate(cObject* obj) override;

};
}
