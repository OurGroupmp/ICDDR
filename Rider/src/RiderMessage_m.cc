//
// Generated file, do not edit! Created by opp_msgtool 6.1 from RiderMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "RiderMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace veins {

Register_Class(RiderMessage)

RiderMessage::RiderMessage(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

RiderMessage::RiderMessage(const RiderMessage& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RiderMessage::~RiderMessage()
{
}

RiderMessage& RiderMessage::operator=(const RiderMessage& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RiderMessage::copy(const RiderMessage& other)
{
    this->roadId = other.roadId;
    this->congestionFactor = other.congestionFactor;
    this->ttl = other.ttl;
    this->isRequest_ = other.isRequest_;
    this->isResponse_ = other.isResponse_;
}

void RiderMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->roadId);
    doParsimPacking(b,this->congestionFactor);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->isRequest_);
    doParsimPacking(b,this->isResponse_);
}

void RiderMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->roadId);
    doParsimUnpacking(b,this->congestionFactor);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->isRequest_);
    doParsimUnpacking(b,this->isResponse_);
}

const char * RiderMessage::getRoadId() const
{
    return this->roadId.c_str();
}

void RiderMessage::setRoadId(const char * roadId)
{
    this->roadId = roadId;
}

int RiderMessage::getCongestionFactor() const
{
    return this->congestionFactor;
}

void RiderMessage::setCongestionFactor(int congestionFactor)
{
    this->congestionFactor = congestionFactor;
}

int RiderMessage::getTtl() const
{
    return this->ttl;
}

void RiderMessage::setTtl(int ttl)
{
    this->ttl = ttl;
}

bool RiderMessage::isRequest() const
{
    return this->isRequest_;
}

void RiderMessage::setIsRequest(bool isRequest)
{
    this->isRequest_ = isRequest;
}

bool RiderMessage::isResponse() const
{
    return this->isResponse_;
}

void RiderMessage::setIsResponse(bool isResponse)
{
    this->isResponse_ = isResponse;
}

class RiderMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_roadId,
        FIELD_congestionFactor,
        FIELD_ttl,
        FIELD_isRequest,
        FIELD_isResponse,
    };
  public:
    RiderMessageDescriptor();
    virtual ~RiderMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RiderMessageDescriptor)

RiderMessageDescriptor::RiderMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::RiderMessage)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

RiderMessageDescriptor::~RiderMessageDescriptor()
{
    delete[] propertyNames;
}

bool RiderMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RiderMessage *>(obj)!=nullptr;
}

const char **RiderMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RiderMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RiderMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RiderMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_roadId
        FD_ISEDITABLE,    // FIELD_congestionFactor
        FD_ISEDITABLE,    // FIELD_ttl
        FD_ISEDITABLE,    // FIELD_isRequest
        FD_ISEDITABLE,    // FIELD_isResponse
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RiderMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "roadId",
        "congestionFactor",
        "ttl",
        "isRequest",
        "isResponse",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RiderMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "roadId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "congestionFactor") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "isRequest") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "isResponse") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RiderMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_roadId
        "int",    // FIELD_congestionFactor
        "int",    // FIELD_ttl
        "bool",    // FIELD_isRequest
        "bool",    // FIELD_isResponse
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RiderMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RiderMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RiderMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RiderMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RiderMessage'", field);
    }
}

const char *RiderMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RiderMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: return oppstring2string(pp->getRoadId());
        case FIELD_congestionFactor: return long2string(pp->getCongestionFactor());
        case FIELD_ttl: return long2string(pp->getTtl());
        case FIELD_isRequest: return bool2string(pp->isRequest());
        case FIELD_isResponse: return bool2string(pp->isResponse());
        default: return "";
    }
}

void RiderMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: pp->setRoadId((value)); break;
        case FIELD_congestionFactor: pp->setCongestionFactor(string2long(value)); break;
        case FIELD_ttl: pp->setTtl(string2long(value)); break;
        case FIELD_isRequest: pp->setIsRequest(string2bool(value)); break;
        case FIELD_isResponse: pp->setIsResponse(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RiderMessage'", field);
    }
}

omnetpp::cValue RiderMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: return pp->getRoadId();
        case FIELD_congestionFactor: return pp->getCongestionFactor();
        case FIELD_ttl: return pp->getTtl();
        case FIELD_isRequest: return pp->isRequest();
        case FIELD_isResponse: return pp->isResponse();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RiderMessage' as cValue -- field index out of range?", field);
    }
}

void RiderMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: pp->setRoadId(value.stringValue()); break;
        case FIELD_congestionFactor: pp->setCongestionFactor(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_ttl: pp->setTtl(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isRequest: pp->setIsRequest(value.boolValue()); break;
        case FIELD_isResponse: pp->setIsResponse(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RiderMessage'", field);
    }
}

const char *RiderMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RiderMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RiderMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RiderMessage *pp = omnetpp::fromAnyPtr<RiderMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RiderMessage'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

