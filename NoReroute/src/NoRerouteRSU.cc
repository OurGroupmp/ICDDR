#include "NoRerouteRSU.h"
#include "NoRerouteMessage_m.h"

using namespace veins;

Define_Module(NoRerouteRSU);

void NoRerouteRSU::onWSA(DemoServiceAdvertisment* wsa)
{
    // Same behavior as demo for now
    // If RSU receives a WSA for service 42, tune to that channel
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
    }
}

void NoRerouteRSU::onWSM(BaseFrame1609_4* frame)
{
    NoRerouteMessage* msg = check_and_cast<NoRerouteMessage*>(frame);

    // TEMPORARY: behave exactly like demo RSU
    // Just rebroadcast after 2 seconds + small random delay
    sendDelayedDown(msg->dup(), 2 + uniform(0.01, 0.2));
}
