/* blpapi_correlationid.h     -*-C++-*- */

#ifndef INCLUDED_API_CORRELATIONID
#define INCLUDED_API_CORRELATIONID

#include <blpapi_types.h>
#include <blpapi_defs.h>

#ifdef __cplusplus 
extern "C" {
#endif

struct blpapi_ManagedPtr_t_;
typedef struct blpapi_ManagedPtr_t_ blpapi_ManagedPtr_t;

typedef int (*blpapi_ManagedPtr_ManagerFunction_t)(
    blpapi_ManagedPtr_t *managedPtr,
    const blpapi_ManagedPtr_t *srcPtr,
    int operation);

struct blpapi_ManagedPtr_t_ {
    void                                *pointer;
    union {
        int   intValue;
        void *ptr;
    } userData[4];
    blpapi_ManagedPtr_ManagerFunction_t  manager;
};

typedef struct blpapi_CorrelationId_t_ {
    unsigned int  size:8;       /* fill in the size of this struct */
    unsigned int  valueType:4;  /* type of value held by this correlation id */
    unsigned int  classId:16;   /* user defined classification id */
    unsigned int  reserved:4;   /* for internal use must be 0 */

    union {
        blpapi_UInt64_t      intValue;
        blpapi_ManagedPtr_t  ptrValue;
    } value;
} blpapi_CorrelationId_t;

BLPAPI_EXPORT
int blpapi_CorrelationId_init(blpapi_CorrelationId_t *correlationId,
                              const blpapi_CorrelationId_t *source);
    /* Initialize the specified 'correlationId'. If the optionally specified
       'source' correlation id is not NULL, then initialize the specified 
       'correlationId' with specified 'source' value. */

BLPAPI_EXPORT
int blpapi_CorrelationId_destroy(const blpapi_CorrelationId_t *cid);

BLPAPI_EXPORT
int blpapi_CorrelationId_assign(blpapi_CorrelationId_t *dst,
                                const blpapi_CorrelationId_t *src);


#ifdef __cplusplus 
}

#include <cstring>
#include <iostream>
#include <algorithm> // for swap

namespace BloombergLP {
namespace blpapi {

                         // ===================
                         // class CorrelationId
                         // ===================
class CorrelationId {
public:
    // PUBLIC TYPES
    enum ValueType {
          UNSET_VALUE   = BLPAPI_CORRELATION_TYPE_UNSET
        , INT_VALUE     = BLPAPI_CORRELATION_TYPE_INT
        , POINTER_VALUE = BLPAPI_CORRELATION_TYPE_POINTER
        , AUTOGEN_VALUE = BLPAPI_CORRELATION_TYPE_AUTOGEN
    };

    enum {
        MAX_CLASS_ID = BLPAPI_CORRELATION_MAX_CLASS_ID
    };

private:
    blpapi_CorrelationId_t d_impl;

    void copy(const blpapi_CorrelationId_t& src);

    template <typename TYPE>
    static int managerFunc(blpapi_ManagedPtr_t *managedPtr,
        const blpapi_ManagedPtr_t *srcPtr, int operation);

    template <typename TYPE>
    static void assertSmartPtrFits();

public:
    // CREATORS
    CorrelationId();
        // Construct a correlation id object initialized to an unset state.

    CorrelationId(const blpapi_CorrelationId_t &correlation);
        // Construct a correlation id object having the same value as the 
        // specified 'correlation' structure. 

    CorrelationId(const CorrelationId& original);
        // Construct a correlation id object having the same value as the 
        // specified 'original' correlation id object. 

    CorrelationId(long long value, int classId = 0);
        // Construct a correlation id object and initialize it with the
        // specified integer 'value'.

    CorrelationId(void *value, int classId = 0);
        // Construct a correlation id object and initialize it with the
        // specified pointer 'value'.

    template<typename TYPE>
    CorrelationId(const TYPE& smartPtr, void *pointerValue, int classId = 0);
        // Construct a correlation id object and initialize it with the
        // specified smart pointer value.

    ~CorrelationId();
        // Destroy this correlation id object.

    // MANIPULATORS
    blpapi_CorrelationId_t& impl();
        // Return a modifiable reference to the underlying correlation id
        // structure contained by this correlation id object.  Note that
        // change the value of the return correlation id structure will directly
        // modify the state of this object. 

    void swap(CorrelationId &rhs);
        // Swap the value of this correlation id object and the specified 'rhs'
        // correlation id object.

    CorrelationId& operator=(const CorrelationId &rhs);
        // Assign to this correlation id objec the value of the specified 'rhs'
        // correlation id object.  Return a modifiable reference to this object.

    // ACCESSORS
    ValueType valueType() const;
        // Return the type of value currently contained by this correlation id.

    unsigned short classId() const;
        // Return the user defined classification of this correlation
        // correlation id object.

    void* asPointer() const;
        // Return the value of this correlation id as a pointer value. Note 
        // that this function assumes that this correlation id object is in a
        // set state and initialized with a pointer value.  The result is
        // undefiend if this assumption is not true.

    template<typename TYPE>
    TYPE asSmartPointer() const;


    long long asInteger() const;
        // Return the value of this correlation id as a pointer value. Note 
        // that this function assumes that this correlation id object is in a
        // set state and initialized with a integer value.  The result is
        // undefiend if this assumption is not true.
    
    const blpapi_CorrelationId_t& impl() const;
        // Return a non-modifiable reference to the underlying correlation id
        // structure contained by this correlation id object.
};

// FREE OPERATOR
inline
bool operator==(const CorrelationId& lhs, const CorrelationId& rhs);
    // Return true if the specified 'lhs' and 'rhs' correlation id objects
    // contain the same value. Return false otherwise. Two correlation id 
    // objects contain the same value of both object have the same 'type()', 
    // 'data1()', and 'data2()' values.

inline
bool operator!=(const CorrelationId& lhs, const CorrelationId& rhs);
    // Return true if the specified 'lhs' and 'rhs' correlation id objects
    // do NOT contain the same value. Return false otherwise. Two correlation 
    // id objects contain the same value of both object have the same 
    // 'type()', 'data1()', and 'data2()' values.

inline
bool operator<(const CorrelationId& lhs, const CorrelationId& rhs);
    // Return true if the value of the specified 'lhs' correlation id object is
    // less than the value of the specified 'rhs' correlation id object.  Return
    // false otherwise.  Note that this function performs a simple raw binary
    // comparision of the specified 'lhs' and 'rhs' objects.  It is provided
    // solely for convience for operations such as insertion into ordered
    // containers.


// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

                         // ===================
                         // class CorrelationId
                         // ===================
// CREATORS
inline CorrelationId::CorrelationId()
{
    std::memset(&d_impl, 0, sizeof(d_impl));
}

inline CorrelationId::CorrelationId(const blpapi_CorrelationId_t &correlationId)
{
    copy(correlationId);
}

inline CorrelationId::CorrelationId(const CorrelationId& src)
{
    copy(src.d_impl);
}

inline CorrelationId::CorrelationId(long long intValue, int classId)
{
    std::memset(&d_impl, 0, sizeof(d_impl));

    d_impl.size           = sizeof(d_impl);
    d_impl.valueType      = INT_VALUE;
    d_impl.value.intValue = intValue;
    d_impl.classId        = classId;
}

inline CorrelationId::CorrelationId(void *ptrValue, int classId)
{
    std::memset(&d_impl, 0, sizeof(d_impl));

    d_impl.size                   = sizeof(d_impl);
    d_impl.valueType              = POINTER_VALUE;
    d_impl.value.ptrValue.pointer = ptrValue;
    d_impl.classId                = classId;
}

template <typename TYPE>
inline CorrelationId::CorrelationId(const TYPE& smartPtr, void *ptrValue,
    int classId)
{
    // If you get a compiler error here, the specified smart pointer does not
    // fit in the CorrelationId and cannot be used at this time.
    assertSmartPtrFits<TYPE>();

    std::memset(&d_impl, 0, sizeof(d_impl));

    d_impl.size           = sizeof(d_impl);
    d_impl.valueType      = POINTER_VALUE;
    d_impl.classId        = classId;

    d_impl.value.ptrValue.pointer = ptrValue;
    d_impl.value.ptrValue.manager = &CorrelationId::managerFunc<TYPE>;

    void *arena = (void *)d_impl.value.ptrValue.userData;
    new (arena) TYPE(smartPtr);
}

inline CorrelationId::~CorrelationId()
{
    if (POINTER_VALUE == valueType()) {
        blpapi_ManagedPtr_ManagerFunction_t &manager =
            d_impl.value.ptrValue.manager;
        if (manager) {
            manager(&d_impl.value.ptrValue, 0, BLPAPI_MANAGEDPTR_DESTROY);
        }
    }
}

// MANIPULATORS
inline void CorrelationId::swap(CorrelationId &rhs)
{
    std::swap(rhs.d_impl, d_impl);
}

inline CorrelationId& CorrelationId::operator=(const CorrelationId &rhs)
{
    if (&rhs == this) return *this;
    CorrelationId tmp(rhs);
    tmp.swap(*this);
    return *this;
}

inline blpapi_CorrelationId_t& CorrelationId::impl() 
{
    return d_impl;
}

// ACCESSORS
inline CorrelationId::ValueType CorrelationId::valueType() const
{
    return (ValueType)d_impl.valueType;
}

inline unsigned short CorrelationId::classId() const
{
    return d_impl.classId;
}

inline void* CorrelationId::asPointer() const
{
    return d_impl.value.ptrValue.pointer;
}

template<typename TYPE>
inline TYPE CorrelationId::asSmartPointer() const
{
    return *(TYPE *)d_impl.value.ptrValue.userData;    
}

inline long long CorrelationId::asInteger() const
{
    return d_impl.value.intValue;
}

inline const blpapi_CorrelationId_t& CorrelationId::impl() const
{
    return d_impl;
}

inline void CorrelationId::copy(const blpapi_CorrelationId_t& src)
{
    d_impl = src;

    if (POINTER_VALUE == valueType()) {
        blpapi_ManagedPtr_ManagerFunction_t& manager =
            d_impl.value.ptrValue.manager;
        if (manager) {
            manager(&d_impl.value.ptrValue, &src.value.ptrValue,
                BLPAPI_MANAGEDPTR_COPY);
        }
    }
}

template <typename TYPE>
inline int CorrelationId::managerFunc(blpapi_ManagedPtr_t *managedPtr,
    const blpapi_ManagedPtr_t *srcPtr, int operation)
{
    if (operation == BLPAPI_MANAGEDPTR_COPY) {
        managedPtr->pointer = srcPtr->pointer;
        managedPtr->manager = srcPtr->manager;

        void *arena = managedPtr->userData;
        new (arena) TYPE(*((TYPE*)&srcPtr->userData[0]));
    }
    else if (operation == BLPAPI_MANAGEDPTR_DESTROY) {
        TYPE *managedPtr_p = (TYPE*)&managedPtr->userData[0];
        managedPtr_p->~TYPE();
    }
    return 0;
}

template <typename TYPE>
inline void CorrelationId::assertSmartPtrFits()
{
    if (false) {
        // If you get a compiler error here, the specified smart pointer does
        // not fit in the CorrelationId and cannot be used at this time.
        char errorIfSmartPtrDoesNotFit[
            sizeof(TYPE) <= (sizeof(void*)*4) ? 1 : 0] = {' '};
    }
}

inline
bool operator==(const CorrelationId& lhs, const CorrelationId& rhs)
{
    if (lhs.valueType() != rhs.valueType()) return false;
    if (lhs.classId() != rhs.classId()) return false;

    if (lhs.valueType() == CorrelationId::POINTER_VALUE) {
        if (lhs.asPointer() != rhs.asPointer())
            return false;
    }
    else if (lhs.asInteger() != rhs.asInteger()) {
        return false;
    }

    return true;
}

inline
bool operator!=(const CorrelationId& lhs, const CorrelationId& rhs)
{
    return !(lhs == rhs);
}

inline
bool operator<(const CorrelationId& lhs, const CorrelationId& rhs)
{
    return std::memcmp(&lhs.impl(), &rhs.impl(), sizeof(rhs.impl())) < 0;
}

inline std::ostream& operator<<(std::ostream& os,
    const BloombergLP::blpapi::CorrelationId& correlator)
{
    const char *valueType = 0;
    switch (correlator.valueType()) {
        case CorrelationId::UNSET_VALUE:   valueType = "UNSET";   break;
        case CorrelationId::INT_VALUE:     valueType = "INT";     break;
        case CorrelationId::POINTER_VALUE: valueType = "POINTER"; break;
        case CorrelationId::AUTOGEN_VALUE: valueType = "AUTOGEN"; break;
        default: valueType = "UNKNOWN";
    }

    os << "[ valueType=" << valueType << " classId=" << correlator.classId()
       << " value=";

    if (correlator.valueType() == CorrelationId::POINTER_VALUE) {
        os << correlator.asPointer();
    }
    else os << correlator.asInteger();
    os << " ]";

    return os;
}

} // namespace BloombergLP {
} // namespace blpapi {

#endif /* __cplusplus */

#endif /* #ifndef INCLUDED_API_CORRELATIONID */

