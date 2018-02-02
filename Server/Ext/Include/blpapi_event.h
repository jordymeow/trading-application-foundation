#ifndef INCLUDED_BLPAPI_EVENT
#define INCLUDED_BLPAPI_EVENT

#include <blpapi_message.h>
#include <blpapi_defs.h>

struct blpapi_Event;
typedef struct blpapi_Event blpapi_Event_t;

struct blpapi_EventQueue;
typedef struct blpapi_EventQueue blpapi_EventQueue_t;

struct blpapi_MessageIterator;
typedef struct blpapi_MessageIterator blpapi_MessageIterator_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
int blpapi_Event_eventType(
        const blpapi_Event_t *event);

BLPAPI_EXPORT
int blpapi_Event_addRef(
        const blpapi_Event_t *event);

BLPAPI_EXPORT
int blpapi_Event_release(
        const blpapi_Event_t *event);



BLPAPI_EXPORT
blpapi_EventQueue_t* blpapi_EventQueue_create();

BLPAPI_EXPORT
int blpapi_EventQueue_destroy(blpapi_EventQueue_t* eventQueue);

BLPAPI_EXPORT
blpapi_Event_t* blpapi_EventQueue_nextEvent(
        blpapi_EventQueue_t *eventQueue,
        int timeout);

BLPAPI_EXPORT
int blpapi_EventQueue_purge(blpapi_EventQueue_t *eventQueue);



BLPAPI_EXPORT
blpapi_MessageIterator_t* blpapi_MessageIterator_create(
        const blpapi_Event_t *event);

BLPAPI_EXPORT
void blpapi_MessageIterator_destroy(
        blpapi_MessageIterator_t* iterator);

BLPAPI_EXPORT
int blpapi_MessageIterator_next(
        blpapi_MessageIterator_t* iterator,
        blpapi_Message_t** result);

#ifdef __cplusplus 
}

namespace BloombergLP {
namespace blpapi {
                         // ===========
                         // class Event
                         // ===========
class Event {
    blpapi_Event_t *d_impl_p;

  public:
    enum EventType {
          ADMIN                 = BLPAPI_EVENTTYPE_ADMIN
        , SESSION_STATUS        = BLPAPI_EVENTTYPE_SESSION_STATUS
        , SUBSCRIPTION_STATUS   = BLPAPI_EVENTTYPE_SUBSCRIPTION_STATUS
        , REQUEST_STATUS        = BLPAPI_EVENTTYPE_REQUEST_STATUS
        , RESPONSE              = BLPAPI_EVENTTYPE_RESPONSE
        , PARTIAL_RESPONSE      = BLPAPI_EVENTTYPE_PARTIAL_RESPONSE
        , SUBSCRIPTION_DATA     = BLPAPI_EVENTTYPE_SUBSCRIPTION_DATA
        , SERVICE_STATUS        = BLPAPI_EVENTTYPE_SERVICE_STATUS
        , TIMEOUT               = BLPAPI_EVENTTYPE_TIMEOUT
        , AUTHORIZATION_STATUS  = BLPAPI_EVENTTYPE_AUTHORIZATION_STATUS
        , UNKNOWN               = -1
    };

    // CREATORS
    Event();
        // Construct an event initialized to an unset state.

    Event(blpapi_Event_t *handle);
        // Construct an event bound to the specified "C" api event handle.

    Event(const Event& original);
        // Construct an event bound to the specified "C" api event handle.

    ~Event();
        // Destroy this event object.  If this object is currently bound to a
        // "C" api event handle then release the reference to it.

    // MANIPULATORS
    Event& operator=(const Event& rhs);

    // ACCESSORS
    EventType eventType() const;
        // Return the type of messages contained by this event.

    bool isValid() const;
        // 

    blpapi_Event_t* impl() const;
        // Return the underlying "C" api event handle that is currently bound to
        // this event object or null if there is no bound handle.
};

                         // ================
                         // class EventQueue
                         // ================

class EventQueue {
    blpapi_EventQueue_t *d_handle_p;
  public:
    //CREATORS
    EventQueue();
        // Construct a empty event queue.

    ~EventQueue();
        // Destroy this event queue and cancel any pending request that is 
        // linked to this queue.

    // MANIPULATORS
    Event nextEvent(int timeout=0);
        // 

    void purge();
        // Purge any messages in this event queue and cancel any pending 
        // requests linked to this queue.  

    // ACCESSORS
    blpapi_EventQueue_t* handle() const;
        // Return the underlying "C" API handle associated with this event 
        // queue.
};

                         // =====================
                         // class MessageIterator
                         // =====================

class MessageIterator {
    blpapi_MessageIterator_t *d_impl_p;
    blpapi_Message_t         *d_current_p;

    // EXPLICITLY DISABLED CREATORS/MANIPULATORS
    MessageIterator(const MessageIterator&); // Not implemented
    MessageIterator& operator=(const MessageIterator&);            // Not implemented

  public: 
    // CREATORS
    MessageIterator(const Event& event);
        // Construct a forward iterator to iterate over the message in the
        // specified 'event' object.  Note that after initialization, this 
        // iterator will be positioned BEFORE the fist message if available.
        // 'next()' must be called to advance to the first message.

    ~MessageIterator();
        // Destroy this iterator object.

    // MANIPULATORS
    bool next();
        // Attempt to advance this iterator object to the next message.  Return
        // 0 on success and a non-zero error code otherwise.
    
    // ACCESSORS
    bool isValid() const;
        // Return true if this iterator is currently positioned on a valid
        // message.  Return false otherwise.

    Message message() const;
        // Return the message at the current position of this iterator.
};

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

                         // -----------
                         // class Event
                         // -----------
// CREATORS
inline Event::Event()
: d_impl_p(0)
{
}

inline Event::Event(blpapi_Event_t *handle)
: d_impl_p(handle)
{
}

inline Event::Event(const Event& original)
: d_impl_p(original.d_impl_p)
{   
    if (d_impl_p) blpapi_Event_addRef(d_impl_p);
}

inline Event::~Event()
{
    if (d_impl_p) blpapi_Event_release(d_impl_p);
}

// MANIPULATORS
inline Event& Event::operator=(const Event& rhs)
{
    if (this == &rhs) return *this;
    if (d_impl_p) blpapi_Event_release(d_impl_p);
    d_impl_p = rhs.d_impl_p;
    if (d_impl_p) blpapi_Event_addRef(d_impl_p);
    return *this;
}

// ACCESSORS
inline Event::EventType Event::eventType() const
{
    return (EventType) blpapi_Event_eventType(d_impl_p);
}

inline bool Event::isValid() const
{
    return d_impl_p ? true : false;
}

inline blpapi_Event_t* Event::impl() const
{
    return d_impl_p;
}

                         // ----------------
                         // class EventQueue
                         // ----------------

inline EventQueue::EventQueue()
{
    d_handle_p = blpapi_EventQueue_create();
}

inline EventQueue::~EventQueue()
{
    blpapi_EventQueue_destroy(d_handle_p);
}

inline Event EventQueue::nextEvent(int timeout)
{
    return blpapi_EventQueue_nextEvent(d_handle_p, timeout); 
}

inline void EventQueue::purge()
{
    blpapi_EventQueue_purge(d_handle_p);
}

inline blpapi_EventQueue_t* EventQueue::handle() const
{
    return d_handle_p;
}

                         // ---------------------
                         // class MessageIterator
                         // ---------------------

inline MessageIterator::MessageIterator(const Event& event)
: d_impl_p(0)
, d_current_p(0)
{
    d_impl_p = blpapi_MessageIterator_create(event.impl());   
}

inline MessageIterator::~MessageIterator()
{
    blpapi_MessageIterator_destroy(d_impl_p);   
}

inline bool MessageIterator::next()
{
    return !blpapi_MessageIterator_next(d_impl_p, &d_current_p);   
}
    
inline bool MessageIterator::isValid() const
{
    return d_current_p ? true : false;
}

inline Message MessageIterator::message() const
{
    return d_current_p;
}


} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_EVENT

