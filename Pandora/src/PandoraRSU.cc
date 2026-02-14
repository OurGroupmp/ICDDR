#include "PandoraRSU.h"
#include "PandoraMessage_m.h"

using namespace veins;

Define_Module(PandoraRSU);

void PandoraRSU::onWSM(BaseFrame1609_4* frame) {
    auto* msg = dynamic_cast<PandoraMessage*>(frame);
    if (!msg) return;

    // Avoid rebroadcast storms
    if (knownCongestedRoads.count(msg->getRoadId()) > 0)
        return;

    knownCongestedRoads.insert(msg->getRoadId());

    // Opportunistic forwarding (acts like AZ support)
    sendDelayedDown(msg->dup(), uniform(0.05, 0.2));
}
