#include "RiderRSU.h"

using namespace veins;

Define_Module(RiderRSU);

void RiderRSU::onWSM(BaseFrame1609_4* frame) {
    delete frame; // RIDER is V2V only
}
