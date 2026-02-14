#include "FCRVehicle.h"
#include "FCRMessage_m.h"

using namespace veins;

Define_Module(FCRVehicle);

void FCRVehicle::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        lastMovedAt = simTime();
        congestionReported = false;
    }
}

void FCRVehicle::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // Detect congestion: very low speed for long time
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastMovedAt > 10 && !congestionReported) {
            congestionReported = true;

            FCRMessage* msg = new FCRMessage();
            populateWSM(msg);
            msg->setMsgType(0); // CONGESTION_REPORT
            msg->setRoadId(mobility->getRoadId().c_str());

            sendDown(msg);
        }
    }
    else {
        lastMovedAt = simTime();
        congestionReported = false;
    }
}

void FCRVehicle::onWSM(BaseFrame1609_4* frame)
{
    FCRMessage* msg = check_and_cast<FCRMessage*>(frame);

    if (msg->getMsgType() == 1) { // REROUTE_GUIDANCE
        if (uniform(0,1) <= msg->getRerouteProb()) {

            const char* targetRoad = msg->getRoadId();

            // Safety: ignore junction edges
            if (targetRoad && targetRoad[0] != ':') {
                traciVehicle->changeRoute(targetRoad, 9999);
                findHost()->getDisplayString().setTagArg("i", 1, "green");
            }
        }
    }
}
