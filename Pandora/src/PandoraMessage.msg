import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.Coord;
import veins.base.utils.SimpleAddress;

namespace veins;

packet PandoraMessage extends BaseFrame1609_4 {
    string roadId;
    double roadWeight;             // w_ij

    // Phase-4: subarea support
    int subareaId;                 // [0..k-1]
    double avgSpeed;               // avg speed observed for this road in this subarea
    int samples;                   // number of samples used in avgSpeed

    Coord criticalCenter;
    double anchorRadius;
    simtime_t timestamp;

    LAddress::L2Type senderAddress = -1;
}
