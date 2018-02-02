#ifndef _INCLUDED_BLOOMBERGLP_BBAPI_SESSION
#define _INCLUDED_BLOOMBERGLP_BBAPI_SESSION

#include <blpapi_types.h>
#include <blpapi_correlationid.h>
#include <blpapi_subscriptionlist.h>
#include <blpapi_event.h>
#include <blpapi_types.h>
#include <blpapi_request.h>
#include <blpapi_service.h>
#include <blpapi_eventdispatcher.h>
#include <blpapi_defs.h>

#ifdef __cplusplus 
extern "C" {
#endif

struct blpapi_Session;
typedef struct blpapi_Session blpapi_Session_t;

struct blpapi_SessionOptions;
typedef struct blpapi_SessionOptions blpapi_SessionOptions_t;

struct blpapi_UserHandle;
typedef struct blpapi_UserHandle blpapi_UserHandle_t;

struct blpapi_SubscriptionItrerator;
typedef struct blpapi_SubscriptionItrerator blpapi_SubscriptionIterator_t;

typedef void(*blpapi_EventHandler_t)(blpapi_Event_t* event,
                                     blpapi_Session_t* session,
                                     void *userData);


BLPAPI_EXPORT
void blpapi_UserHandle_release(blpapi_UserHandle_t* handle);

BLPAPI_EXPORT
int blpapi_UserHandle_addRef(blpapi_UserHandle_t* handle);

BLPAPI_EXPORT
int blpapi_UserHandle_hasEntitlements(
        const blpapi_UserHandle_t* handle,
        const blpapi_Service_t *service, 
        const blpapi_Element_t *eidElement, 
        const int *entitlementIds, 
        size_t numEntitlements,
        int *failedEntitlements,
        int *failedEntitlementsCount);


BLPAPI_EXPORT
blpapi_Session_t* blpapi_Session_create(
        blpapi_SessionOptions_t *parameters, 
        blpapi_EventHandler_t handler, 
        blpapi_EventDispatcher_t* dispatcher,
        void *userData);

BLPAPI_EXPORT
void blpapi_Session_destroy(
        blpapi_Session_t *session);
        
BLPAPI_EXPORT
int blpapi_Session_start(
        blpapi_Session_t *session);

BLPAPI_EXPORT
int blpapi_Session_startAsync(
        blpapi_Session_t *session);

BLPAPI_EXPORT
int blpapi_Session_stop(
        blpapi_Session_t* session);

BLPAPI_EXPORT
int blpapi_Session_stopAsync(
        blpapi_Session_t* session);

BLPAPI_EXPORT
int blpapi_Session_nextEvent(
        blpapi_Session_t* session, 
        blpapi_Event_t **eventPointer,
        unsigned int timeoutInMilliseconds);

BLPAPI_EXPORT
int blpapi_Session_subscribe(
        blpapi_Session_t *session,
        const blpapi_SubscriptionList_t *subscriptionList,
        const blpapi_UserHandle_t* handle,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_resubscribe(
        blpapi_Session_t *session,
        const blpapi_SubscriptionList_t *resubscriptionList,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_unsubscribe(
        blpapi_Session_t *session,
        const blpapi_SubscriptionList_t *desubscriptionList,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_cancel(
        blpapi_Session_t *session,
        const blpapi_CorrelationId_t *correlationIds,
        unsigned numCorrelationIds,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_sendRequest(
        blpapi_Session_t *session,
        const blpapi_Request_t *request,
        blpapi_CorrelationId_t *correlationId,
        blpapi_UserHandle_t *userHandle,
        blpapi_EventQueue_t *eventQueue,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_sendAuthorizationRequest(
        blpapi_Session_t *session,
        const blpapi_Request_t *request,
        blpapi_UserHandle_t *userHandle,
        blpapi_CorrelationId_t *correlationId,
        blpapi_EventQueue_t *eventQueue,
        const char *requestLabel,
        int requestLabelLen);

BLPAPI_EXPORT
int blpapi_Session_openService(
        blpapi_Session_t *session,
        const char* serviceName);

BLPAPI_EXPORT
int blpapi_Session_openServiceAsync(
        blpapi_Session_t *session,
        const char* serviceName,
        blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_Session_getService(
        blpapi_Session_t *session,
        blpapi_Service_t **service,
        const char* serviceName);

BLPAPI_EXPORT
blpapi_UserHandle_t* blpapi_Session_createUserHandle(
        blpapi_Session_t *session);

BLPAPI_EXPORT
void blpapi_Session_destroyUserHandle(
        blpapi_Session_t *session,
        blpapi_UserHandle_t* handle);

BLPAPI_EXPORT
blpapi_SessionOptions_t* blpapi_SessionOptions_create();

BLPAPI_EXPORT
void blpapi_SessionOptions_destroy(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerHost(
        blpapi_SessionOptions_t *parameters,
        const char* serverHost);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerPort(
        blpapi_SessionOptions_t *parameters,
        unsigned short serverPort);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerAddress(
        blpapi_SessionOptions_t *parameters,
		const char* serverHost,
        unsigned short serverPort,
		size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_removeServerAddress(
        blpapi_SessionOptions_t *parameters,		
		size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_setConnectTimeout(
        blpapi_SessionOptions_t *parameters,
        unsigned int connectTimeoutInSeconds);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultServices(
        blpapi_SessionOptions_t *parameters,
        const char* defaultServices);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultSubscriptionService(
        blpapi_SessionOptions_t *parameters,
        const char* defaultSubscriptionService);

BLPAPI_EXPORT
void blpapi_SessionOptions_setDefaultTopicPrefix(
        blpapi_SessionOptions_t *parameters,
        const char* defaultTopicPrefix);

BLPAPI_EXPORT
void blpapi_SessionOptions_setAllowMultipleCorrelatorsPerMsg(
        blpapi_SessionOptions_t *parameters,
        int allowMultipleCorrelatorsPerMsg);

BLPAPI_EXPORT
void blpapi_SessionOptions_setClientMode(
        blpapi_SessionOptions_t *parameters,
        int clientMode);

BLPAPI_EXPORT
void blpapi_SessionOptions_setMaxPendingRequests(
        blpapi_SessionOptions_t *parameters,
        int maxPendingRequests);

#ifdef __cplusplus 
BLPAPI_EXPORT
void blpapi_SessionOptions_setAutoRestartOnDisconnection(
        blpapi_SessionOptions_t *parameters,
		bool                     autoRestart);
#endif

BLPAPI_EXPORT
void blpapi_SessionOptions_setAutoRestart(
        blpapi_SessionOptions_t *parameters,
		int                     autoRestart);


BLPAPI_EXPORT
const char* blpapi_SessionOptions_serverHost(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
unsigned int blpapi_SessionOptions_serverPort(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_numServerAddresses(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_getServerAddress(
        blpapi_SessionOptions_t *parameters,
		const char** serverHost,
		unsigned short *serverPort,
		size_t index);

BLPAPI_EXPORT
unsigned int blpapi_SessionOptions_connectTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionOptions_defaultServices(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionOptions_defaultSubscriptionService( 
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionOptions_defaultTopicPrefix( 
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_allowMultipleCorrelatorsPerMsg( 
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_clientMode( 
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_maxPendingRequests( 
        blpapi_SessionOptions_t *parameters);

#ifdef __cplusplus 
BLPAPI_EXPORT
bool blpapi_SessionOptions_autoRestartOnDisconnection( 
        blpapi_SessionOptions_t *parameters);
#endif

BLPAPI_EXPORT
int blpapi_SessionOptions_autoRestart( 
        blpapi_SessionOptions_t *parameters);



BLPAPI_EXPORT
blpapi_SubscriptionIterator_t* blpapi_SubscriptionItr_create(
        blpapi_Session_t *session);

BLPAPI_EXPORT
void blpapi_SubscriptionItr_destroy(
        blpapi_SubscriptionIterator_t *iterator);

BLPAPI_EXPORT
int blpapi_SubscriptionItr_next(
        blpapi_SubscriptionIterator_t *iterator,
        const char** subscriptionString,
        blpapi_CorrelationId_t *correlationId,
        int *status);

BLPAPI_EXPORT
int blpapi_SubscriptionItr_isValid(
        const blpapi_SubscriptionIterator_t *iterator);

#ifdef __cplusplus 
}

#include <cstring> // for std::memset

namespace BloombergLP {
namespace blpapi {

static void eventHandlerProxy(blpapi_Event_t* event, blpapi_Session_t *session,
                              void *userData);
class Session;
                         // ================
                         // class UserHandle
                         // ================

class UserHandle {
    blpapi_UserHandle_t *d_handle_p;

    void addRef();
    void release();

public:
    // CREATORS
    UserHandle();

    UserHandle(blpapi_UserHandle_t *handle);

    UserHandle(const UserHandle&);

    ~UserHandle();
        // Destroy this user handle and cancel ay authorization(s) associated
        // with it.

    // MANIPULATORS
    UserHandle& operator=(const UserHandle&); // Not implemented

    // ACCESSORS
    bool hasEntitlements(const Service& service, 
                         const int *entitlementIds, 
                         size_t count,
                         int *failedEntitlements=0,
                         int *failedEntitlementsCount=0) const;
        // Return true if this user handle is authorized for the specified 
        // 'service' and is entitled to the specified 'entitlementIds' 
        // associated with the the specifed 'service'.  Return false 
        // otherwise.  // TODO: adjust docs

    bool hasEntitlements(const Service& service, 
                         const Element& entitlementIds,
                         int *failedEntitlements,
                         int *failedEntitlementsCount) const;
        // Return true if this user handle is authorized for the specified 
        // 'service' and is entitled to the specified entitlement id(s) 
        // contained in the specified 'entitlementIds' element associated with 
        // the the specifed 'service'.  Return false otherwise. Note that if 
        // 'entitlementIds' contains multiple identifiers, then this user 
        // handle must be entitled to ALL of the handles, otherwise false is
        // returned.  // TODO: adjust docs 

    bool isValid() const;
    
    blpapi_UserHandle_t* handle() const;
        // Return the underlying API handle associated with this user 
        // handle.
};

                         // ==================
                         // class EventHandler
                         // ==================

class EventHandler {
    // This class provides a pure abstract interface for handling events
  public:
	virtual bool processEvent(const Event& event,
        Session *session) = 0;
};

                         // ====================
                         // class SessionOptions
                         // ====================

class SessionOptions {
    blpapi_SessionOptions_t *d_handle_p;

public:
    enum ClientMode {
        AUTO = BLPAPI_CLIENTMODE_AUTO            
      , DAPI = BLPAPI_CLIENTMODE_DAPI
      , SAPI = BLPAPI_CLIENTMODE_SAPI
    };

    // CREATORS/DESTRUCTORS
    SessionOptions();

    ~SessionOptions();

    // MANIUPLATORS
    void setServerHost(const char* host);

    void setServerPort(unsigned short port);

	int setServerAddress(const char*    serverHost,
						 unsigned short serverPort,
						 size_t         index);

	int removeServerAddress(size_t index);

    void setConnectTimeout(unsigned int);

    void setDefaultServices(const char* defaultServices);

    void setDefaultSubscriptionService(const char* defaultSubscriptionService);
    
    void setDefaultTopicPrefix(const char* defaultTopicPrefix);

    void setAllowMultipleCorrelatorsPerMsg(bool allowMultipleCorrelatorsPerMsg);

	void setClientMode(int clientMode);

	void setMaxPendingRequests(int maxPendingRequests);

	void setAutoRestartOnDisconnection(bool autoRestart);
	

    // ACCESSOR
    const char* serverHost() const;

    unsigned short serverPort() const;
	
	size_t numServerAddresses() const;

	int getServerAddress(const char**    serverHost,
						 unsigned short* serverPort,
						 size_t          index) const;

    unsigned int connectTimeout() const;

    const char* defaultServices() const;

    const char* defaultSubscriptionService() const;

    const char* defaultTopicPrefix() const;

    bool allowMultipleCorrelatorsPerMsg() const;

	int clientMode() const;

    blpapi_SessionOptions_t* handle() const;

	int maxPendingRequests() const;

	bool autoRestartOnDisconnection() const;
};

                         // =============
                         // class Session
                         // =============

class Session {
    // This class provides a session for making requests for Bloomberg services.
    blpapi_Session_t            *d_handle_p;
    EventHandler                *d_eventHandler_p;

    // EXPLICITLY DISABLED CREATORS/MANIPULATORS
    Session(const Session&); // Not implemented
    Session& operator=(const Session&); // Not implemented

    friend void eventHandlerProxy(blpapi_Event_t* event,
        blpapi_Session_t *session, void *userData);

    void dispatchEvent(const Event& event);

public:
    enum SubscriptionStatus {
          UNSUBSCRIBED         = BLPAPI_SUBSCRIPTIONSTATUS_UNSUBSCRIBED
        , SUBSCRIBING          = BLPAPI_SUBSCRIPTIONSTATUS_SUBSCRIBING
        , SUBSCRIBED           = BLPAPI_SUBSCRIPTIONSTATUS_SUBSCRIBED
        , CANCELLED            = BLPAPI_SUBSCRIPTIONSTATUS_CANCELLED
        , PENDING_CANCELLATION = BLPAPI_SUBSCRIPTIONSTATUS_PENDING_CANCELLATION
    };

	Session(const SessionOptions& options = SessionOptions(),
			EventHandler* eventHandler=0, 
			EventDispatcher* eventDispatcher=0);
        // Construct a session using the specified session options and the 
        // optionally specified 'eventHandler' and
        // 'eventDispatcher' dispatcher.  If an 'eventHandler' is specified then
        // this session will operate in asynchronous mode, otherwise the session
        // will operate in synchronous mode.  In synchronous mode, all events
        // will be delivered directly to the eventHandler as they are received.
        // In synchronous, the call must call 'nextEvent()' to retrieve the next
        // event.  Note that 'nextEvent()' cannot be called in asynchronous
        // mode.  If in asynchronous mode and 'eventDispatcher' is specified,
        // then all events will be dispatched to the event handler using the
        // supplied event dispatcher.  The event dispatcher allows for the
        // control over how many threads of execution are used to process
        // events.  Multiple events can be simultaneously dispatched using an
        // event dispatcher.  Note that even when multiple threads are used for
        // dispatching events, the logical ordering of events such as updates
        // for a subscription request, or multiple responses for a single
        // request, will be maintained.

	~Session();
        // Destroy this session.

	// MANIPULATORS
	bool start();
        // 

	bool startAsync();
        // Begin operation of this session.

	void stop();
        // Stop operation of this session. 

	void stopAsync();

	Event nextEvent(int timeout=0);
        // Retrieve the next available event for this session.  If no event is
        // available, wait up to the optionally specified 'timeout'
        // milliseconds for an event to arrive.  If no event is received before
        // that timeout expires, return an event of type 'EventType::TIMEOUT'.  If
        // timeout is not specified or is specified as 0, then wait for an
        // infinite amount of time for an event to be received.  If an error
        // occurrs, return a null event.  Note that this function cannot be
        // called on a session that is operating in "asynchronous" mode.  That
        // is a session that was constructed with an event handler.  Attempting
        // to do so will result in an InvalidState exception. 

    bool openService(const char* uri);
        // Open the service having the specified 'uri'.  The specified 'uri'
        // must contain a fully qualified service name.  That is it must be of
        // the form "//<namespace>/<service-name>" or
        // "//<namespace>/service-name>/<topic>?<options>".  If the 'uri'
        // contains a topic and/or options, they will be ignored.  Return zero
        // on success and a non-zero error code on failure.  Note that this
        // operation is a blocking operation which may require communication to
        // server-side services.  Execution may be be blocked for an
        // undetermined amount of time.  If blocking is not desired, then use
        // 'openServiceAsync' instead.  Also note that if the service is 
        // already opened by this session, the request will succeed
        // immediatedly.

    CorrelationId openServiceAsync(const char* uri,
        const CorrelationId& correlationId = CorrelationId());
        // Initiate a requst to open the service having the specified 'uri'.
        // The specified 'uri' must contain a fully qualified service name.  
        // That is it must be of the form "//<namespace>/<service-name>" or
        // "//<namespace>/service-name>/<topic>?<options>".  If the 'uri'
        // contains a topic and/or options, they will be ignored.  Return zero
        // if the request was asynchronously initiated, and a non-zero error
        // code on otherwise.  Once the request has completed, a
        // "SERVICE_STAUTS" event will be generated indicating the result of the
        // request.  If the optionally specified 'correlationId' is supplied,
        // then it will be returned in generated message. It can also be used to
        // cancel this request before it completes by calling the 'cancel'
        // operation.  Note that if supplied, 'correlationId' MUST BE unique
        // from any "active" correlation supplied to this session via any
        // operation(e.g., "subscribe", "sendRequest").  A correlation id is active
        // if the request for which it was supplied is still pending, or if it
        // refers to a subscription request that has not been terminated either 
        // explicitly or by an unsolicited termination. 

	// SUBSCRIPTION MANIPULATORS
	void subscribe(
            const SubscriptionList& subscriptionList, 
            const UserHandle& userHandle,
            const char *requestLabel = 0,
            int requestLabelLen = 0);
	void subscribe(const SubscriptionList& subscriptionList,
            const char *requestLabel = 0,
            int requestLabelLen = 0);
        // TODO: adjust doc to match this prototype
        // Initiate a request to receive asynchronous updates to the topic
        // specified by the supplied 'subscriptionString'. Associated with 
        // this request, the specified 'correlationId'. Throw exception if this
        // request was not successfully initiated. Uppon completion of the request, 
		// a "SUBSCRIPTION_STATUS" event will be
        // generated containing a message with the result of the request. If the
        // subscription request is successful, a "SubscriptionStarted" message
        // will be generated and the subscription is initiated.  If the request fails, a 
        // "SubscriptionFailure" message containing the failure reason will be 
        // generated. Once initiated, "SUBSCRIPTION_DATA" events will be generated
        // containing topic specific update messages as they are recieved until
        // the subscription is terminated.  The subscription can be explicitly
        // terminated using the supplied 'correlationId' by calling either 
        // 'unsubscribe' or 'cancel'.  The subscription can also be terminated at 
        // any time by an unsolicited server-side cancellation.  Upon receipt of an
        // unsolicited cancelation, a "SubscriptionLost" message containing the 
        // termination reason will be generated and delivered via a
        // "SUBSCRIPTION_STATUS" event. Note that ALL messages generated for this 
        // request will contain the supplied 
        // 'correlationId'.  Also Note that the supplied, 'correlationId' MUST BE unique
        // from any "active" correlation ids supplied to this session via any
        // operation(e.g., "subscribe", "sendRequest").  A correlation id is active
        // if the request for which it was supplied is still pending, or if it
        // refers to a subscription request that has not been terminated either 
        // explicitly or by an unsolicited termination.
    
	void unsubscribe(const SubscriptionList& subscriptionList);
        // Cancel previous requests for asynchronous topic updates associated
        // with the correlation ids listed in the specified 'subscriptionList'.  
        // Return zero on success and a non-zero error code otherwise. This
        // operation provides a batch form of the single-subscription
        // 'unsubscribe' operation above.  See that 'unsubscribe' operation 
        // for more information the handling of each individual unsubscribe
        // request, and other important notes.

	void resubscribe(const SubscriptionList& subscriptions,
        const char *requestLabel = 0,
        int requestLabelLen = 0);

	// REQUEST/RESPONSE MANIUPLATORS
	CorrelationId sendRequest(
        const Request&, 
        const CorrelationId& correlationId=CorrelationId(),
        EventQueue *eventQueue=0,
        const char *requestLabel = 0,
        int requestLabelLen = 0);

	CorrelationId sendRequest(
        const Request&, 
        const UserHandle& user,
        const CorrelationId& correlationId=CorrelationId(),
        EventQueue *eventQueue=0,
        const char *requestLabel = 0,
        int requestLabelLen = 0);

    CorrelationId sendAuthorizationRequest(
        const Request& authorizationRequest, 
        UserHandle *userHandle,
        const CorrelationId& correlationId=CorrelationId(),
        EventQueue* eventQueue=0);

    void cancel(const CorrelationId& correlationId);
        // Cancel the previous request associated with the specified
        // 'correlationId'.  Return zero on success and a non-zero error code
        // otherwise.

    void cancel(const std::vector<CorrelationId>& correlationIds);

    void cancel(const CorrelationId* correlationIds,
               size_t numCorrelationIds);

    UserHandle createUserHandle();

	// ACCESSORS
    Service getService(const char* serviceName) const;
        // Return a service object having the specified 'serviceName'.  If the
        // service name is not yet open, attempt to open it first.  If the
        // service cannout be opened, throw and exception indicating the error.

    blpapi_Session_t* handle() const;
}; 


class SubscriptionIterator {
    blpapi_SubscriptionIterator_t *d_handle_p;
    const char     *d_subscriptionString;
    CorrelationId   d_correlationId;
    int             d_status;
    bool            d_isValid;

    // EXPLICITLY DISABLED CREATORS/MANIPULATORS
	SubscriptionIterator(const SubscriptionIterator&); // Not implemented
    SubscriptionIterator& 
    operator=(const SubscriptionIterator&); // Not implemented

  public:
    // CREATORS
	SubscriptionIterator(Session *session);
        // Construct a forward iterator to iterate over the subscriptions of the
        // specified 'session' object.  Note that after initialization, this 
        // iterator will be positioned BEFORE the fist subscription record 
        // if available.  'next()' must be called to advance to the first 
        // subscription.

	~SubscriptionIterator();
        // Destroy this subscription iterator.

    // MANIUPLATORS
	bool next();
        // Attempt to advance this iterator to the next subscription record.  
        // Return 0 on success and a non-zero error code otherwise.

    // ACCESSORS
	bool isValid() const;
        // Return true if this iterator is currently positioned on a valid
        // subscription record.  Return false otherwise.

    blpapi_SubscriptionIterator_t* handle() const;
        // Return the underlying API handle associated with this
        // subscription iterator.

    const char* subscriptionString() const;

    const CorrelationId& correlationId() const;

    Session::SubscriptionStatus subscriptionStatus() const;
};

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

inline UserHandle::UserHandle()
    : d_handle_p(0)
{
    //d_handle_p = blpapi_UserHandle_create();
}

inline UserHandle::UserHandle(blpapi_UserHandle_t *handle)
    : d_handle_p(handle)
{
    // Assumes ownership of the raw user handle
    // addRef();
}

inline UserHandle::UserHandle(const UserHandle& src)
    : d_handle_p(src.d_handle_p)
{
    addRef();
}

inline UserHandle::~UserHandle()
{
    release();
}

inline UserHandle& UserHandle::operator=(const UserHandle& rhs)
{
    release();

    d_handle_p = rhs.d_handle_p;
    addRef();

    return *this;
}

inline void UserHandle::addRef()
{
    blpapi_UserHandle_addRef(d_handle_p);
}

inline void UserHandle::release()
{
    if (d_handle_p)
        blpapi_UserHandle_release(d_handle_p);    
}

// ACCESSORS
inline bool UserHandle::hasEntitlements(
        const Service& service, 
        const int *entitlementIds, 
        size_t numEntitlements,
        int *failedEntitlements,
        int *failedEntitlementsCount) const
{
    return blpapi_UserHandle_hasEntitlements(
            d_handle_p,
            service.handle(),
            0,
            entitlementIds,
            numEntitlements,
            failedEntitlements,
            failedEntitlementsCount) ? true : false;
}

inline bool UserHandle::hasEntitlements(
        const Service& service, 
        const Element& entitlementIds,
        int *failedEntitlements,
        int *failedEntitlementsCount) const
{
    return blpapi_UserHandle_hasEntitlements(
            d_handle_p,
            service.handle(),
            entitlementIds.handle(),
            0,
            0,
            failedEntitlements,
            failedEntitlementsCount) ? true : false;
}

inline bool UserHandle::isValid() const
{
    return (d_handle_p != 0);
}

inline blpapi_UserHandle_t* UserHandle::handle() const
{
    return d_handle_p;
}

               // -------
               // Session
               // -------

inline Service Session::getService(const char* serviceName) const
{
    blpapi_Service_t *service;
    ExceptionUtil::throwOnError(
            blpapi_Session_getService(d_handle_p, 
                                      &service, 
                                      serviceName));
    return service;
}

inline Session::Session(const SessionOptions& parameters, 
                        EventHandler* handler, 
                        EventDispatcher* dispatcher)
    : d_eventHandler_p(handler)
{
    d_handle_p = blpapi_Session_create(
            parameters.handle(), 
            handler ? (blpapi_EventHandler_t)eventHandlerProxy : 0,
            dispatcher ? dispatcher->impl() : 0,
            this);
}

inline Session::~Session()
{
    blpapi_Session_destroy(d_handle_p);
}

inline bool Session::start()
{
    return blpapi_Session_start(d_handle_p) ? false : true;
}

inline bool Session::startAsync()
{
    return blpapi_Session_startAsync(d_handle_p) ? false : true;
}

inline void  Session::stop()
{
    blpapi_Session_stop(d_handle_p);
}

inline void  Session::stopAsync()
{
    blpapi_Session_stopAsync(d_handle_p);
}

inline Event Session::nextEvent(int timeout)
{
    blpapi_Event_t *event;
    blpapi_Session_nextEvent(d_handle_p, &event, timeout);
    return Event(event);
}

	// SUBSCRIPTION MANIPULATORS
inline void Session::subscribe(const SubscriptionList& subscriptions,
                              const char *requestLabel,
                              int requestLabelLen)
{
    ExceptionUtil::throwOnError(
		blpapi_Session_subscribe(d_handle_p, subscriptions.impl(),
	        0, requestLabel, requestLabelLen)
	);
}

inline void Session::subscribe(const SubscriptionList& subscriptions, 
                              const UserHandle& userHandle,
                              const char *requestLabel,
                              int requestLabelLen)
{
    ExceptionUtil::throwOnError(
		blpapi_Session_subscribe(d_handle_p, subscriptions.impl(),
	        userHandle.handle(), requestLabel, requestLabelLen)
	);
}

inline void Session::resubscribe(const SubscriptionList& subscriptions,
                                const char *requestLabel,
                                int requestLabelLen)
{
    ExceptionUtil::throwOnError(
		blpapi_Session_resubscribe(d_handle_p, subscriptions.impl(),
	        requestLabel, requestLabelLen)
	);
}

inline void Session::unsubscribe(const SubscriptionList& list)
{
    ExceptionUtil::throwOnError(
		blpapi_Session_unsubscribe(d_handle_p, list.impl(), 0, 0)
	);
}




inline CorrelationId Session::sendRequest(
        const Request& request, 
        const UserHandle& userHandle,
        const CorrelationId& correlationId,
        EventQueue *eventQueue,
        const char *requestLabel,
        int requestLabelLen)
{
    CorrelationId retCorrelationId(correlationId);

    ExceptionUtil::throwOnError(blpapi_Session_sendRequest(
        d_handle_p, 
        request.handle(), 
        const_cast<blpapi_CorrelationId_t *>(&retCorrelationId.impl()),
        userHandle.handle(),
        eventQueue ? eventQueue->handle() : 0,
        requestLabel,
        requestLabelLen));

    return retCorrelationId;
}

inline CorrelationId Session::sendRequest(
        const Request& request, 
        const CorrelationId& correlationId,
        EventQueue *eventQueue,
        const char *requestLabel,
        int requestLabelLen)
{
    CorrelationId retCorrelationId(correlationId);

    ExceptionUtil::throwOnError(blpapi_Session_sendRequest(
            d_handle_p, 
            request.handle(), 
            const_cast<blpapi_CorrelationId_t *>(&retCorrelationId.impl()),
            0,
            eventQueue ? eventQueue->handle() : 0,
            requestLabel,
            requestLabelLen));

    return retCorrelationId;
}

inline CorrelationId Session::sendAuthorizationRequest(
        const Request& authorizationRequest, 
        UserHandle *userHandle,
        const CorrelationId& correlationId,
        EventQueue *eventQueue)
{
    CorrelationId retCorrelationId(correlationId);

    ExceptionUtil::throwOnError(blpapi_Session_sendAuthorizationRequest(
            d_handle_p, 
            authorizationRequest.handle(), 
            userHandle->handle(),
            const_cast<blpapi_CorrelationId_t *>(&retCorrelationId.impl()),
            eventQueue ? eventQueue->handle() : 0, 0, 0));

    return retCorrelationId;
}

inline void Session::cancel(const CorrelationId& correlationId)
{
    blpapi_Session_cancel(d_handle_p, &correlationId.impl(), 1, 0, 0);
}

inline void Session::cancel(const std::vector<CorrelationId>& correlationIds)
{
    if (!correlationIds.size()) return;
    cancel(&correlationIds[0], correlationIds.size());
}

inline void Session::cancel(const CorrelationId* correlationIds,
                           size_t numCorrelationIds)
{
    blpapi_Session_cancel(
            d_handle_p, 
            reinterpret_cast<const blpapi_CorrelationId_t*>(correlationIds),
            numCorrelationIds, 0, 0);
}

inline bool Session::openService(const char* uri)
{
    return blpapi_Session_openService(d_handle_p, uri) ? false : true;
}

inline CorrelationId Session::openServiceAsync(const char* uri,
                                               const CorrelationId& correlationId)
{
	blpapi_CorrelationId_t retv = correlationId.impl();
	ExceptionUtil::throwOnError(
		blpapi_Session_openServiceAsync(
			d_handle_p, 
			uri,
			&retv)
			//const_cast<blpapi_CorrelationId_t *>(&correlationId.impl()))
	);
   
    return retv;
}

inline UserHandle Session::createUserHandle()
{
    return blpapi_Session_createUserHandle(d_handle_p);
}

inline blpapi_Session_t* Session::handle() const
{
    return d_handle_p;
}

inline
void Session::dispatchEvent(const Event& event)
{
    d_eventHandler_p->processEvent(event, this);
}

inline SessionOptions::SessionOptions()
{
    d_handle_p = blpapi_SessionOptions_create();
}

inline SessionOptions::~SessionOptions()
{
    blpapi_SessionOptions_destroy(d_handle_p);
}

// MANIPULATOR
inline void SessionOptions::setServerHost(const char* serverHost)
{
    blpapi_SessionOptions_setServerHost( d_handle_p, serverHost);
}

inline void SessionOptions::setServerPort(unsigned short serverPort)
{
    blpapi_SessionOptions_setServerPort( d_handle_p, serverPort);
}

inline int SessionOptions::setServerAddress(
						 const char*    serverHost,
						 unsigned short serverPort,
						 size_t         index)
{
	return blpapi_SessionOptions_setServerAddress(d_handle_p, serverHost, serverPort, index);
}

inline int SessionOptions::removeServerAddress(size_t index)
{
	return blpapi_SessionOptions_removeServerAddress(d_handle_p, index);
}

inline void SessionOptions::setConnectTimeout(unsigned int timeout)
{
    blpapi_SessionOptions_setConnectTimeout(d_handle_p, timeout);
}

inline void SessionOptions::setDefaultServices(const char* defaultServices)
{
    blpapi_SessionOptions_setDefaultServices(d_handle_p, defaultServices);
}

inline void SessionOptions::setDefaultSubscriptionService(const char* defaultSubscriptionService)
{
    blpapi_SessionOptions_setDefaultSubscriptionService(
            d_handle_p,
            defaultSubscriptionService);
}

inline void SessionOptions::setDefaultTopicPrefix(const char* defaultTopicPrefix)
{
    blpapi_SessionOptions_setDefaultTopicPrefix(
            d_handle_p,
            defaultTopicPrefix);
}

inline void SessionOptions::setAllowMultipleCorrelatorsPerMsg(bool allowMultipleCorrelatorsPerMsg)
{
    blpapi_SessionOptions_setAllowMultipleCorrelatorsPerMsg(
            d_handle_p,
            allowMultipleCorrelatorsPerMsg);
}

inline void SessionOptions::setClientMode(int clientMode)
{
    blpapi_SessionOptions_setClientMode(
            d_handle_p,
            clientMode);
}

inline void SessionOptions::setMaxPendingRequests(int maxPendingRequests)
{
	blpapi_SessionOptions_setMaxPendingRequests(		
			d_handle_p, 
			maxPendingRequests);
}

inline void SessionOptions::setAutoRestartOnDisconnection(bool autoRestart)
{
	blpapi_SessionOptions_setAutoRestartOnDisconnection(		
			d_handle_p, 
			autoRestart);
}


inline const char* SessionOptions::serverHost() const
{
    return blpapi_SessionOptions_serverHost(d_handle_p);
}

inline unsigned short SessionOptions::serverPort() const
{
    return blpapi_SessionOptions_serverPort(d_handle_p);
}

inline size_t SessionOptions::numServerAddresses() const
{
	return blpapi_SessionOptions_numServerAddresses(d_handle_p);
}

inline int SessionOptions::getServerAddress(
							const char**    serverHost,
							unsigned short* serverPort,
							size_t          index) const
{
	return blpapi_SessionOptions_getServerAddress(
				d_handle_p, serverHost, serverPort, index);
}

inline unsigned int SessionOptions::connectTimeout() const
{
    return blpapi_SessionOptions_connectTimeout(d_handle_p);
}

inline const char* SessionOptions::defaultServices() const
{
    return blpapi_SessionOptions_defaultServices(d_handle_p);
}

inline const char* SessionOptions::defaultSubscriptionService() const
{
    return blpapi_SessionOptions_defaultSubscriptionService(d_handle_p);
}

inline const char* SessionOptions::defaultTopicPrefix() const
{
    return blpapi_SessionOptions_defaultTopicPrefix(d_handle_p);
}

inline bool SessionOptions::allowMultipleCorrelatorsPerMsg() const
{
    return blpapi_SessionOptions_allowMultipleCorrelatorsPerMsg(d_handle_p) ? true : false;
}

inline int SessionOptions::clientMode() const
{
    return blpapi_SessionOptions_clientMode(d_handle_p);
}

inline int SessionOptions::maxPendingRequests() const
{
	return blpapi_SessionOptions_maxPendingRequests(d_handle_p);
}

inline bool SessionOptions::autoRestartOnDisconnection() const
{
	return blpapi_SessionOptions_autoRestartOnDisconnection(d_handle_p);
}


inline blpapi_SessionOptions_t* SessionOptions::handle() const
{
    return d_handle_p;
}

static void eventHandlerProxy(blpapi_Event_t* event, blpapi_Session_t *session,
                              void *userData)
{
    reinterpret_cast<Session*>(userData)->dispatchEvent(Event(event));
}

inline SubscriptionIterator::SubscriptionIterator(Session *session)
    : d_isValid(false)
{
    d_handle_p = blpapi_SubscriptionItr_create(session->handle());
}

inline SubscriptionIterator::~SubscriptionIterator()
{
    blpapi_SubscriptionItr_destroy(d_handle_p);
}

inline bool SubscriptionIterator::next()
{
    d_isValid = !blpapi_SubscriptionItr_next(d_handle_p, &d_subscriptionString,
        const_cast<blpapi_CorrelationId_t *>(&d_correlationId.impl()),
        &d_status);

    return d_isValid;
}

inline bool SubscriptionIterator::isValid() const
{
    return d_isValid;
}

inline blpapi_SubscriptionIterator_t* SubscriptionIterator::handle() const
{
    return d_handle_p;
}

inline const char* SubscriptionIterator::subscriptionString() const
{
    if (isValid()) return d_subscriptionString;

    ExceptionUtil::throwOnError(BLPAPI_ERROR_ILLEGAL_STATE);
}

inline const CorrelationId& SubscriptionIterator::correlationId() const
{
    if (isValid()) return d_correlationId;

    ExceptionUtil::throwOnError(BLPAPI_ERROR_ILLEGAL_STATE);
}

inline
Session::SubscriptionStatus SubscriptionIterator::subscriptionStatus() const
{
    if (isValid()) return static_cast<Session::SubscriptionStatus>(d_status);

    ExceptionUtil::throwOnError(BLPAPI_ERROR_ILLEGAL_STATE);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif /* ifdef __cplusplus  */

#endif /* _INCLUDED_BLOOMBERGLP_BBAPI_SESSION */
