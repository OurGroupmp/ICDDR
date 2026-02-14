#pragma once

#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include <set>
#include <string>

namespace veins {

class PandoraRSU : public DemoBaseApplLayer {
protected:
    std::set<std::string> knownCongestedRoads;

    virtual void onWSM(BaseFrame1609_4* wsm) override;
};

}
