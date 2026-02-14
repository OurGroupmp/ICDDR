import veins.modules.messages.BaseFrame1609_4;

namespace veins;

packet RiderMessage extends BaseFrame1609_4 {
    string roadId;
    int congestionFactor;
    int ttl;
    bool isRequest;
    bool isResponse;
}
