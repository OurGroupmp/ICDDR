#include "FCRRSU.h"
#include "FCRMessage_m.h"
#include <cmath>

using namespace veins;

Define_Module(FCRRSU);

void FCRRSU::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        roadFlow.clear();
        roadCapacity.clear();
    }
}

void FCRRSU::updateFlow(const std::string& roadId)
{
    roadFlow[roadId]++;

    // Initialize base capacity once
    if (roadCapacity.find(roadId) == roadCapacity.end()) {
        roadCapacity[roadId] = 20;   // base road capacity
    }
}

double FCRRSU::computeRerouteProbability(const std::string& roadId)
{
    int flow = roadFlow[roadId];
    int cap  = roadCapacity[roadId];

    if (flow <= cap) return 0.0;

    // ---- Phase-4 logic ----
    // Excess flow ratio
    double excessRatio = (double)(flow - cap) / cap;

    // Turn/intersection penalty (paper-style abstraction)
    double turnPenalty = 1.2;  // models right-turn / signal loss

    // Compliance factor α
    double alpha = 0.8;

    // Smooth escalation (avoids oscillations)
    double prob = alpha * (1 - std::exp(-turnPenalty * excessRatio));

    return std::min(1.0, prob);
}

void FCRRSU::onWSM(BaseFrame1609_4* frame)
{
    FCRMessage* msg = check_and_cast<FCRMessage*>(frame);

    if (msg->getMsgType() == 0) { // CONGESTION_REPORT

        std::string road = msg->getRoadId();
        updateFlow(road);

        double rerouteProb = computeRerouteProbability(road);
        if (rerouteProb <= 0) return;

        // Instruct vehicles to avoid congestion
        FCRMessage* guide = new FCRMessage();
        populateWSM(guide);

        guide->setMsgType(1);           // REROUTE_GUIDANCE
        guide->setRoadId(road.c_str()); // road to avoid
        guide->setRerouteProb(rerouteProb);

        sendDelayedDown(guide, 1);
    }
}
