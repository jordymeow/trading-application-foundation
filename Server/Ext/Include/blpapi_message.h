// blpapi_message.h     -*-C++-*-
#ifndef INCLUDED_BLPAPI_MESSAGE
#define INCLUDED_BLPAPI_MESSAGE

#include <blpapi_element.h>
#include <blpapi_correlationid.h>
#include <blpapi_defs.h>
#include <blpapi_service.h>

struct blpapi_Message;
typedef struct blpapi_Message blpapi_Message_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Name_t* blpapi_Message_messageType(
        const blpapi_Message_t *message);

BLPAPI_EXPORT
const char* blpapi_Message_typeString(
        const blpapi_Message_t *message);

BLPAPI_EXPORT
const char* blpapi_Message_topicName(
        const blpapi_Message_t *message);

BLPAPI_EXPORT
blpapi_Service_t* blpapi_Message_service(
        const blpapi_Message_t *message);

BLPAPI_EXPORT
int blpapi_Message_numCorrelationIds(
        const blpapi_Message_t *message);

BLPAPI_EXPORT
blpapi_CorrelationId_t blpapi_Message_correlationId(
        const blpapi_Message_t *message,
        size_t index);

BLPAPI_EXPORT
blpapi_Element_t* blpapi_Message_elements(
        const blpapi_Message_t *message);

#ifdef __cplusplus 
}

namespace BloombergLP {
namespace blpapi {

#include <iosfwd>

class Message {
    // This class provides access to a message.
    // TODO: proper docs

    blpapi_Message_t *d_handle;   // API handle associated with this message
    Element           d_elements; // Top-level element associated with this
                                  // message

  public:
    // CREATORS
    Message(blpapi_Message_t *handle);
        // TODO: 

    ~Message();
        // Destroy this message object.

    // ACCESSORS
    Name messageType() const;
        // Return the name assocaited with this message.  

    const char* topicName() const;
        // Return a non-modifiable pointer to the topic string associated with
        // this message.  Return an empty string if there is no topic assocaited
        // with this message.  Note that the returned pointer is only valid while
        // this message is valid.

    Service service() const;
        // Return the service from which this this message originated. 

    int numCorrelationIds() const;
        // Return the number of correlation ids associated with this message.

    CorrelationId correlationId(size_t index=0) const;
        // Return the 'index'th correlation id associated with this message.
        // Throw exception of 'index' >= 'numCorrelationIds()'.

    bool hasElement(const Name& name, bool excludeNullElements=false) const;
    bool hasElement(const char* name, bool excludeNullElements=false) const;
        // Return true of this message contains an element having the specified
        // 'name'.  Return false otherwise.

    size_t numElements() const;
        // Return the number of elements contained by this message.

    const Element getElement(const Name& name) const;
    const Element getElement(const char* name) const;
        // Return the element of this message having the specified 'name'.
        // Throw exception if this message does not contain an element having
        // the specified 'name'.

    bool getElementAsBool(const Name& name) const;
    bool getElementAsBool(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // boolean value.  Throw exception if no element having the specified
        // 'name' exists in this message, or it it exists, but does not have a
        // value, or if the value is not convertible to a boolean value.

    char getElementAsChar(const Name& name) const;
    char getElementAsChar(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // character value.  Throw exception if no element having the specified
        // 'name' exists in this message, or it it exists, but does not have a
        // value, or if the value is not convertible to a character value.

    Int32 getElementAsInt32(const Name& name) const;
    Int32 getElementAsInt32(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // 32bit integer value.  Throw exception if no element having the specified
        // 'name' exists in this message, or it it exists, but does not have a
        // value, or if the value is not convertible to a 32bit integer value.

    Int64 getElementAsInt64(const Name& name) const;
    Int64 getElementAsInt64(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // 64bit integer value.  Throw exception if no element having the specified
        // 'name' exists in this message, or it it exists, but does not have a
        // value, or if the value is not convertible to a 64bit integer value.

    Float32 getElementAsFloat32(const Name& name) const;
    Float32 getElementAsFloat32(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // 32bit floating point value.  Throw exception if no element having 
        // the specified 'name' exists in this message, or it it exists, but
        //  does not have a value, or if the value is not convertible to a 
        // 32bit floating point value.

    Float64 getElementAsFloat64(const Name& name) const;
    Float64 getElementAsFloat64(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // 64bit floating point value.  Throw exception if no element having 
        // the specified 'name' exists in this message, or it it exists, but
        //  does not have a value, or if the value is not convertible to a 
        // 64bit floating point value.

    Datetime getElementAsDatetime(const Name& name) const;
    Datetime getElementAsDatetime(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // Date/Time value.  Throw exception if no element having 
        // the specified 'name' exists in this message, or it it exists, but
        //  does not have a value, or if the value is not convertible to a 
        // Date/Time value.

    const char* getElementAsString(const Name& name) const;
    const char* getElementAsString(const char* name) const;
        // Return the value of the element having the specified 'name' as a
        // string value.  Throw exception if no element having 
        // the specified 'name' exists in this message, or it it exists, but
        //  does not have a value, or if the value is not convertible to a 
        // string value.

    const Element asElement() const;
        // Return an non-modifiable reference to the top-level element of this
        // message object.  The top-level elements contains all messages
        // normally accessible through the "getElement" functions.

    std::ostream& print(std::ostream& stream,
                        int level=0, 
                        int spacesPerLevel=4) const; 
        // Format the contents of this message to the specified 'stream'.
};

std::ostream& operator<<(std::ostream& stream, const Message &request);
    // TODO: doc

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

inline Message::Message(blpapi_Message_t *handle)
: d_handle(handle)
{
    if (handle) d_elements = Element(blpapi_Message_elements(handle));
}


inline Message::~Message()
{
}


// ACCESSORS
inline Name Message::messageType() const
{
    return blpapi_Message_messageType(d_handle);
}

inline const char* Message::topicName() const
{
    return blpapi_Message_topicName(d_handle);
}

inline Service Message::service() const
{
    return blpapi_Message_service(d_handle);
}

inline int Message::numCorrelationIds() const
{
    return blpapi_Message_numCorrelationIds(d_handle);
}

inline CorrelationId Message::correlationId(size_t index) const
{
    // TODO: throw on error
    return blpapi_Message_correlationId(d_handle, index);
}

inline bool Message::hasElement(const char* name,
                                bool excludeNullElements) const
{
    return d_elements.hasElement(name, excludeNullElements);
}

inline bool Message::hasElement(const Name& name,
                                bool excludeNullElements) const
{
    return d_elements.hasElement(name, excludeNullElements);
}

inline size_t Message::numElements() const
{
    return d_elements.numElements();
}

inline const Element Message::getElement(const Name& name) const
{
    return d_elements.getElement(name);
}

inline const Element Message::getElement(const char* nameString) const
{
    return d_elements.getElement(nameString);
}

inline bool Message::getElementAsBool(const Name& name) const
{
    return d_elements.getElementAsBool(name);
}

inline bool Message::getElementAsBool(const char* name) const
{
    return d_elements.getElementAsBool(name);
}

inline char Message::getElementAsChar(const Name& name) const
{
    return d_elements.getElementAsChar(name);
}

inline char Message::getElementAsChar(const char* name) const
{
    return d_elements.getElementAsChar(name);
}

inline Int32 Message::getElementAsInt32(const Name& name) const
{
    return d_elements.getElementAsInt32(name);
}

inline Int32 Message::getElementAsInt32(const char* name) const
{
    return d_elements.getElementAsInt32(name);
}

inline Int64 Message::getElementAsInt64(const Name& name) const
{
    return d_elements.getElementAsInt64(name);
}

inline Int64 Message::getElementAsInt64(const char* name) const
{
    return d_elements.getElementAsInt64(name);
}

inline Float32 Message::getElementAsFloat32(const Name& name) const
{
    return d_elements.getElementAsFloat32(name);
}

inline Float32 Message::getElementAsFloat32(const char* name) const
{
    return d_elements.getElementAsFloat32(name);
}

inline Float64 Message::getElementAsFloat64(const Name& name) const
{
    return d_elements.getElementAsFloat64(name);
}

inline Float64 Message::getElementAsFloat64(const char* name) const
{
    return d_elements.getElementAsFloat64(name);
}

inline Datetime Message::getElementAsDatetime(const Name& name) const
{
    return d_elements.getElementAsDatetime(name);
}

inline Datetime Message::getElementAsDatetime(const char* name) const
{
    return d_elements.getElementAsDatetime(name);
}

inline const char* Message::getElementAsString(const Name& name) const
{
    return d_elements.getElementAsString(name);
}

inline const char* Message::getElementAsString(const char* name) const
{
    return d_elements.getElementAsString(name);
}

inline const Element Message::asElement() const
{
    return d_elements;
}

inline std::ostream& Message::print(
        std::ostream& stream,
        int level, 
        int spacesPerLevel) const
{
    return d_elements.print(stream, level, spacesPerLevel);
}

inline std::ostream& operator<<(std::ostream& stream, const Message &message)
{
    return message.print(stream, 0,-1);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus
    
#endif // #ifndef INCLUDED_BLPAPI_MESSAGE

