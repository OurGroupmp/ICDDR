#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

namespace veins {

class NoRerouteRSU : public DemoBaseApplLayer {
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
    void onWSA(DemoServiceAdvertisment* wsa) override;
};

}
