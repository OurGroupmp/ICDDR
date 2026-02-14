#include "NoRerouteVehicle.h"
#include "NoRerouteMessage_m.h"

using namespace veins;

Define_Module(NoRerouteVehicle);

void NoRerouteVehicle::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
}

void NoRerouteVehicle::onWSA(DemoServiceAdvertisment* wsa)
{
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(static_cast<Channel>(wsa->getTargetChannel()));
        currentSubscribedServiceId = wsa->getPsid();
        if (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService(static_cast<Channel>(wsa->getTargetChannel()),
                         wsa->getPsid(),
                         "NoReroute Service");
        }
    }
}

void NoRerouteVehicle::onWSM(BaseFrame1609_4* frame)
{
    NoRerouteMessage* msg = check_and_cast<NoRerouteMessage*>(frame);

    findHost()->getDisplayString().setTagArg("i", 1, "green");

    // TEMP: same behavior as demo
    if (mobility->getRoadId()[0] != ':')
        traciVehicle->changeRoute(msg->getRoadId(), 9999);

    if (!sentMessage) {
        sentMessage = true;
        msg->setSenderAddress(myId);
        scheduleAt(simTime() + 2 + uniform(0.01, 0.2), msg->dup());
    }
}

void NoRerouteVehicle::handleSelfMsg(cMessage* msg)
{
    if (NoRerouteMessage* wsm = dynamic_cast<NoRerouteMessage*>(msg)) {
        sendDown(wsm->dup());
        delete wsm;
    }
    else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void NoRerouteVehicle::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // TEMP: same demo trigger
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10 && sentMessage == false) {
            findHost()->getDisplayString().setTagArg("i", 1, "red");
            sentMessage = true;

            NoRerouteMessage* msg = new NoRerouteMessage();
            populateWSM(msg);
            msg->setRoadId(mobility->getRoadId().c_str());

            sendDown(msg);
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
