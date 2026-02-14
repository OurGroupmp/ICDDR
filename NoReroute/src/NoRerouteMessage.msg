import veins.base.utils.Coord;
import veins.modules.messages.BaseFrame1609_4;
import veins.base.utils.SimpleAddress;

namespace veins;

packet NoRerouteMessage extends BaseFrame1609_4 {
    string roadId;
    LAddress::L2Type senderAddress = -1;
}
