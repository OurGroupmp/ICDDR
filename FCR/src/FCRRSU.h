#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include <map>
#include <string>

namespace veins {

class FCRRSU : public DemoBaseApplLayer {
protected:
    std::map<std::string, int> roadFlow;
    std::map<std::string, int> roadCapacity;

    virtual void initialize(int stage) override;
    virtual void onWSM(BaseFrame1609_4* wsm) override;

    void updateFlow(const std::string& roadId);
    double computeRerouteProbability(const std::string& roadId);
};

}
