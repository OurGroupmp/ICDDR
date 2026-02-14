import veins.modules.messages.BaseFrame1609_4;

namespace veins;

packet FCRMessage extends BaseFrame1609_4
{
    int msgType;          // 0 = CONGESTION_REPORT, 1 = REROUTE_GUIDANCE
    string roadId;        // always a VALID SUMO edge id
    double rerouteProb;   // α
}
