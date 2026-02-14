import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

// Vehicle -> RSU: report low-speed condition (alpha breach)
packet ICDDRSpeedReport extends BaseFrame1609_4 {
    string roadId;                     // SUMO edge id
    LAddress::L2Type senderAddress = -1;
    double v20;                        // avg speed estimate (m/s)
    double vFree;                      // free flow estimate (m/s)
    double alpha;                      // v20 / vFree
    double senderX;
    double senderY;
}

// RSU/Vehicle -> Vehicle: Congestion Alert Message (CAM)
packet ICDDRCAM extends BaseFrame1609_4 {
    string camId;                      // unique id: rsuId-edge-seq
    string roadId;                     // congested edge id
    int ttl;                           // adaptive TTL (max forwards)
    int hopsLeft;                      // decremented at each forward
    double cd;                         // congestion score
    int seqNo;                         // optional

    // Sender Travel Path Line (TPL) parameters for relevance calc
    double senderSlope;
    double senderIntercept;
    double senderX;
    double senderY;
}
