#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"

namespace veins {

class RiderRSU : public DemoBaseApplLayer {
protected:
    void onWSM(BaseFrame1609_4* wsm) override;
};

}
