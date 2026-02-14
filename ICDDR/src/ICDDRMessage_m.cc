//
// Generated file, do not edit! Created by opp_msgtool 6.1 from ICDDRMessage.msg.
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
#include "ICDDRMessage_m.h"

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

Register_Class(ICDDRSpeedReport)

ICDDRSpeedReport::ICDDRSpeedReport(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

ICDDRSpeedReport::ICDDRSpeedReport(const ICDDRSpeedReport& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

ICDDRSpeedReport::~ICDDRSpeedReport()
{
}

ICDDRSpeedReport& ICDDRSpeedReport::operator=(const ICDDRSpeedReport& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void ICDDRSpeedReport::copy(const ICDDRSpeedReport& other)
{
    this->roadId = other.roadId;
    this->senderAddress = other.senderAddress;
    this->v20 = other.v20;
    this->vFree = other.vFree;
    this->alpha = other.alpha;
    this->senderX = other.senderX;
    this->senderY = other.senderY;
}

void ICDDRSpeedReport::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->roadId);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->v20);
    doParsimPacking(b,this->vFree);
    doParsimPacking(b,this->alpha);
    doParsimPacking(b,this->senderX);
    doParsimPacking(b,this->senderY);
}

void ICDDRSpeedReport::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->roadId);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->v20);
    doParsimUnpacking(b,this->vFree);
    doParsimUnpacking(b,this->alpha);
    doParsimUnpacking(b,this->senderX);
    doParsimUnpacking(b,this->senderY);
}

const char * ICDDRSpeedReport::getRoadId() const
{
    return this->roadId.c_str();
}

void ICDDRSpeedReport::setRoadId(const char * roadId)
{
    this->roadId = roadId;
}

const LAddress::L2Type& ICDDRSpeedReport::getSenderAddress() const
{
    return this->senderAddress;
}

void ICDDRSpeedReport::setSenderAddress(const LAddress::L2Type& senderAddress)
{
    this->senderAddress = senderAddress;
}

double ICDDRSpeedReport::getV20() const
{
    return this->v20;
}

void ICDDRSpeedReport::setV20(double v20)
{
    this->v20 = v20;
}

double ICDDRSpeedReport::getVFree() const
{
    return this->vFree;
}

void ICDDRSpeedReport::setVFree(double vFree)
{
    this->vFree = vFree;
}

double ICDDRSpeedReport::getAlpha() const
{
    return this->alpha;
}

void ICDDRSpeedReport::setAlpha(double alpha)
{
    this->alpha = alpha;
}

double ICDDRSpeedReport::getSenderX() const
{
    return this->senderX;
}

void ICDDRSpeedReport::setSenderX(double senderX)
{
    this->senderX = senderX;
}

double ICDDRSpeedReport::getSenderY() const
{
    return this->senderY;
}

void ICDDRSpeedReport::setSenderY(double senderY)
{
    this->senderY = senderY;
}

class ICDDRSpeedReportDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_roadId,
        FIELD_senderAddress,
        FIELD_v20,
        FIELD_vFree,
        FIELD_alpha,
        FIELD_senderX,
        FIELD_senderY,
    };
  public:
    ICDDRSpeedReportDescriptor();
    virtual ~ICDDRSpeedReportDescriptor();

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

Register_ClassDescriptor(ICDDRSpeedReportDescriptor)

ICDDRSpeedReportDescriptor::ICDDRSpeedReportDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::ICDDRSpeedReport)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

ICDDRSpeedReportDescriptor::~ICDDRSpeedReportDescriptor()
{
    delete[] propertyNames;
}

bool ICDDRSpeedReportDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ICDDRSpeedReport *>(obj)!=nullptr;
}

const char **ICDDRSpeedReportDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ICDDRSpeedReportDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ICDDRSpeedReportDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int ICDDRSpeedReportDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_roadId
        0,    // FIELD_senderAddress
        FD_ISEDITABLE,    // FIELD_v20
        FD_ISEDITABLE,    // FIELD_vFree
        FD_ISEDITABLE,    // FIELD_alpha
        FD_ISEDITABLE,    // FIELD_senderX
        FD_ISEDITABLE,    // FIELD_senderY
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ICDDRSpeedReportDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "roadId",
        "senderAddress",
        "v20",
        "vFree",
        "alpha",
        "senderX",
        "senderY",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ICDDRSpeedReportDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "roadId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "senderAddress") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "v20") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "vFree") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "alpha") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "senderX") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "senderY") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *ICDDRSpeedReportDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_roadId
        "veins::LAddress::L2Type",    // FIELD_senderAddress
        "double",    // FIELD_v20
        "double",    // FIELD_vFree
        "double",    // FIELD_alpha
        "double",    // FIELD_senderX
        "double",    // FIELD_senderY
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ICDDRSpeedReportDescriptor::getFieldPropertyNames(int field) const
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

const char *ICDDRSpeedReportDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ICDDRSpeedReportDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ICDDRSpeedReportDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ICDDRSpeedReport'", field);
    }
}

const char *ICDDRSpeedReportDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ICDDRSpeedReportDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: return oppstring2string(pp->getRoadId());
        case FIELD_senderAddress: return "";
        case FIELD_v20: return double2string(pp->getV20());
        case FIELD_vFree: return double2string(pp->getVFree());
        case FIELD_alpha: return double2string(pp->getAlpha());
        case FIELD_senderX: return double2string(pp->getSenderX());
        case FIELD_senderY: return double2string(pp->getSenderY());
        default: return "";
    }
}

void ICDDRSpeedReportDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: pp->setRoadId((value)); break;
        case FIELD_v20: pp->setV20(string2double(value)); break;
        case FIELD_vFree: pp->setVFree(string2double(value)); break;
        case FIELD_alpha: pp->setAlpha(string2double(value)); break;
        case FIELD_senderX: pp->setSenderX(string2double(value)); break;
        case FIELD_senderY: pp->setSenderY(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRSpeedReport'", field);
    }
}

omnetpp::cValue ICDDRSpeedReportDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: return pp->getRoadId();
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        case FIELD_v20: return pp->getV20();
        case FIELD_vFree: return pp->getVFree();
        case FIELD_alpha: return pp->getAlpha();
        case FIELD_senderX: return pp->getSenderX();
        case FIELD_senderY: return pp->getSenderY();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ICDDRSpeedReport' as cValue -- field index out of range?", field);
    }
}

void ICDDRSpeedReportDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        case FIELD_roadId: pp->setRoadId(value.stringValue()); break;
        case FIELD_v20: pp->setV20(value.doubleValue()); break;
        case FIELD_vFree: pp->setVFree(value.doubleValue()); break;
        case FIELD_alpha: pp->setAlpha(value.doubleValue()); break;
        case FIELD_senderX: pp->setSenderX(value.doubleValue()); break;
        case FIELD_senderY: pp->setSenderY(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRSpeedReport'", field);
    }
}

const char *ICDDRSpeedReportDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ICDDRSpeedReportDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        case FIELD_senderAddress: return omnetpp::toAnyPtr(&pp->getSenderAddress()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ICDDRSpeedReportDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRSpeedReport *pp = omnetpp::fromAnyPtr<ICDDRSpeedReport>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRSpeedReport'", field);
    }
}

Register_Class(ICDDRCAM)

ICDDRCAM::ICDDRCAM(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

ICDDRCAM::ICDDRCAM(const ICDDRCAM& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

ICDDRCAM::~ICDDRCAM()
{
}

ICDDRCAM& ICDDRCAM::operator=(const ICDDRCAM& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void ICDDRCAM::copy(const ICDDRCAM& other)
{
    this->camId = other.camId;
    this->roadId = other.roadId;
    this->ttl = other.ttl;
    this->hopsLeft = other.hopsLeft;
    this->cd = other.cd;
    this->seqNo = other.seqNo;
    this->senderSlope = other.senderSlope;
    this->senderIntercept = other.senderIntercept;
    this->senderX = other.senderX;
    this->senderY = other.senderY;
}

void ICDDRCAM::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->camId);
    doParsimPacking(b,this->roadId);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->hopsLeft);
    doParsimPacking(b,this->cd);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->senderSlope);
    doParsimPacking(b,this->senderIntercept);
    doParsimPacking(b,this->senderX);
    doParsimPacking(b,this->senderY);
}

void ICDDRCAM::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->camId);
    doParsimUnpacking(b,this->roadId);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->hopsLeft);
    doParsimUnpacking(b,this->cd);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->senderSlope);
    doParsimUnpacking(b,this->senderIntercept);
    doParsimUnpacking(b,this->senderX);
    doParsimUnpacking(b,this->senderY);
}

const char * ICDDRCAM::getCamId() const
{
    return this->camId.c_str();
}

void ICDDRCAM::setCamId(const char * camId)
{
    this->camId = camId;
}

const char * ICDDRCAM::getRoadId() const
{
    return this->roadId.c_str();
}

void ICDDRCAM::setRoadId(const char * roadId)
{
    this->roadId = roadId;
}

int ICDDRCAM::getTtl() const
{
    return this->ttl;
}

void ICDDRCAM::setTtl(int ttl)
{
    this->ttl = ttl;
}

int ICDDRCAM::getHopsLeft() const
{
    return this->hopsLeft;
}

void ICDDRCAM::setHopsLeft(int hopsLeft)
{
    this->hopsLeft = hopsLeft;
}

double ICDDRCAM::getCd() const
{
    return this->cd;
}

void ICDDRCAM::setCd(double cd)
{
    this->cd = cd;
}

int ICDDRCAM::getSeqNo() const
{
    return this->seqNo;
}

void ICDDRCAM::setSeqNo(int seqNo)
{
    this->seqNo = seqNo;
}

double ICDDRCAM::getSenderSlope() const
{
    return this->senderSlope;
}

void ICDDRCAM::setSenderSlope(double senderSlope)
{
    this->senderSlope = senderSlope;
}

double ICDDRCAM::getSenderIntercept() const
{
    return this->senderIntercept;
}

void ICDDRCAM::setSenderIntercept(double senderIntercept)
{
    this->senderIntercept = senderIntercept;
}

double ICDDRCAM::getSenderX() const
{
    return this->senderX;
}

void ICDDRCAM::setSenderX(double senderX)
{
    this->senderX = senderX;
}

double ICDDRCAM::getSenderY() const
{
    return this->senderY;
}

void ICDDRCAM::setSenderY(double senderY)
{
    this->senderY = senderY;
}

class ICDDRCAMDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_camId,
        FIELD_roadId,
        FIELD_ttl,
        FIELD_hopsLeft,
        FIELD_cd,
        FIELD_seqNo,
        FIELD_senderSlope,
        FIELD_senderIntercept,
        FIELD_senderX,
        FIELD_senderY,
    };
  public:
    ICDDRCAMDescriptor();
    virtual ~ICDDRCAMDescriptor();

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

Register_ClassDescriptor(ICDDRCAMDescriptor)

ICDDRCAMDescriptor::ICDDRCAMDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::ICDDRCAM)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

ICDDRCAMDescriptor::~ICDDRCAMDescriptor()
{
    delete[] propertyNames;
}

bool ICDDRCAMDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ICDDRCAM *>(obj)!=nullptr;
}

const char **ICDDRCAMDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ICDDRCAMDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ICDDRCAMDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int ICDDRCAMDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_camId
        FD_ISEDITABLE,    // FIELD_roadId
        FD_ISEDITABLE,    // FIELD_ttl
        FD_ISEDITABLE,    // FIELD_hopsLeft
        FD_ISEDITABLE,    // FIELD_cd
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_senderSlope
        FD_ISEDITABLE,    // FIELD_senderIntercept
        FD_ISEDITABLE,    // FIELD_senderX
        FD_ISEDITABLE,    // FIELD_senderY
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *ICDDRCAMDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "camId",
        "roadId",
        "ttl",
        "hopsLeft",
        "cd",
        "seqNo",
        "senderSlope",
        "senderIntercept",
        "senderX",
        "senderY",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int ICDDRCAMDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "camId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "roadId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopsLeft") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "cd") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "seqNo") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "senderSlope") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "senderIntercept") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "senderX") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "senderY") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *ICDDRCAMDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_camId
        "string",    // FIELD_roadId
        "int",    // FIELD_ttl
        "int",    // FIELD_hopsLeft
        "double",    // FIELD_cd
        "int",    // FIELD_seqNo
        "double",    // FIELD_senderSlope
        "double",    // FIELD_senderIntercept
        "double",    // FIELD_senderX
        "double",    // FIELD_senderY
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **ICDDRCAMDescriptor::getFieldPropertyNames(int field) const
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

const char *ICDDRCAMDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ICDDRCAMDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ICDDRCAMDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ICDDRCAM'", field);
    }
}

const char *ICDDRCAMDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ICDDRCAMDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        case FIELD_camId: return oppstring2string(pp->getCamId());
        case FIELD_roadId: return oppstring2string(pp->getRoadId());
        case FIELD_ttl: return long2string(pp->getTtl());
        case FIELD_hopsLeft: return long2string(pp->getHopsLeft());
        case FIELD_cd: return double2string(pp->getCd());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_senderSlope: return double2string(pp->getSenderSlope());
        case FIELD_senderIntercept: return double2string(pp->getSenderIntercept());
        case FIELD_senderX: return double2string(pp->getSenderX());
        case FIELD_senderY: return double2string(pp->getSenderY());
        default: return "";
    }
}

void ICDDRCAMDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        case FIELD_camId: pp->setCamId((value)); break;
        case FIELD_roadId: pp->setRoadId((value)); break;
        case FIELD_ttl: pp->setTtl(string2long(value)); break;
        case FIELD_hopsLeft: pp->setHopsLeft(string2long(value)); break;
        case FIELD_cd: pp->setCd(string2double(value)); break;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); break;
        case FIELD_senderSlope: pp->setSenderSlope(string2double(value)); break;
        case FIELD_senderIntercept: pp->setSenderIntercept(string2double(value)); break;
        case FIELD_senderX: pp->setSenderX(string2double(value)); break;
        case FIELD_senderY: pp->setSenderY(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRCAM'", field);
    }
}

omnetpp::cValue ICDDRCAMDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        case FIELD_camId: return pp->getCamId();
        case FIELD_roadId: return pp->getRoadId();
        case FIELD_ttl: return pp->getTtl();
        case FIELD_hopsLeft: return pp->getHopsLeft();
        case FIELD_cd: return pp->getCd();
        case FIELD_seqNo: return pp->getSeqNo();
        case FIELD_senderSlope: return pp->getSenderSlope();
        case FIELD_senderIntercept: return pp->getSenderIntercept();
        case FIELD_senderX: return pp->getSenderX();
        case FIELD_senderY: return pp->getSenderY();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ICDDRCAM' as cValue -- field index out of range?", field);
    }
}

void ICDDRCAMDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        case FIELD_camId: pp->setCamId(value.stringValue()); break;
        case FIELD_roadId: pp->setRoadId(value.stringValue()); break;
        case FIELD_ttl: pp->setTtl(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hopsLeft: pp->setHopsLeft(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_cd: pp->setCd(value.doubleValue()); break;
        case FIELD_seqNo: pp->setSeqNo(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_senderSlope: pp->setSenderSlope(value.doubleValue()); break;
        case FIELD_senderIntercept: pp->setSenderIntercept(value.doubleValue()); break;
        case FIELD_senderX: pp->setSenderX(value.doubleValue()); break;
        case FIELD_senderY: pp->setSenderY(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRCAM'", field);
    }
}

const char *ICDDRCAMDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr ICDDRCAMDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ICDDRCAMDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ICDDRCAM *pp = omnetpp::fromAnyPtr<ICDDRCAM>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ICDDRCAM'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

