// blpapi_subscriptionhandle.h     -*-C++-*-
#ifndef INCLUDED_BLPAPI_SUBSCRIPTIONHANDLE_H
#define INCLUDED_BLPAPI_SUBSCRIPTIONHANDLE_H

#include <blpapi_correlationid.h>

#ifndef INCLUDED_BCEMA_SHAREDPTR
#include <bcema_sharedptr.h>
#endif

#ifndef INCLUDED_BLPAPI_HANDLE
#include <blpapi_handle.h>
#endif

#ifndef INCLUDED_REQUESTHANDLE_H
#include <blpapi_requesthandle.h>
#endif

#ifndef INCLUDED_API_DEFS
#include <blpapi_defs.h>
#endif

#include <string>

namespace BloombergLP {
namespace blpapi {
    
class SchemaTypeDefImpl;
class ServiceImpl;
class UserHandleImpl;

class SubscriptionHandle : public RequestHandle {
  public:
    enum Status {
          UNSUBSCRIBED         = BLPAPI_SUBSCRIPTIONSTATUS_UNSUBSCRIBED
        , SUBSCRIBING          = BLPAPI_SUBSCRIPTIONSTATUS_SUBSCRIBING
        , SUBSCRIBED           = BLPAPI_SUBSCRIPTIONSTATUS_SUBSCRIBED
        , CANCELLED            = BLPAPI_SUBSCRIPTIONSTATUS_CANCELLED
        , PENDING_CANCELLATION = BLPAPI_SUBSCRIPTIONSTATUS_PENDING_CANCELLATION
    };

  private:
    HandleRef<std::string>                   d_topicString;
	std::string                              d_subscriptionString;
	bcema_SharedPtr<std::string>             d_requestLabel_p;
    CorrelationId                            d_correlationId;
    Int64                                    d_handle;    

    HandleRef<const ServiceImpl>             d_service_sp;   // Schema for root realtimve events 
    bcema_SharedPtr<const SchemaTypeDefImpl> d_schema_sp;    // Schema for root realtimve events 
    Status                                   d_status;  
    HandleRef<UserHandleImpl>                d_userHandle_sp; // Schema for root realtimve events 
    int                                      d_instanceId;  
	bool                                     d_isFailOver;

  public:
    // CREATORS
    SubscriptionHandle(
            CorrelationId id, 
			const HandleRef<std::string> & topicString,
			const std::string& subscriptionString,
			const bcema_SharedPtr<std::string> & requestLabel_p,
            const HandleRef<UserHandleImpl> &userHandle=HandleRef<UserHandleImpl>(),
            int instanceId=0);

    // MANIUPLATORS
    void setHandle(Int64 handle);

    void setStatus(SubscriptionHandle::Status status);

    void setSchema(const bcema_SharedPtr<const SchemaTypeDefImpl>& schema);

    void setService(const HandleRef<const ServiceImpl>& service);

	void setFailOver(bool isFailOver);

    // ACCESSORS
    const CorrelationId& correlationId() const;

    const HandleRef<std::string>& topicString() const;

	const std::string& subscriptionString() const;

    Int64 handle() const;

    const HandleRef<const ServiceImpl>& service() const;

    const bcema_SharedPtr<const SchemaTypeDefImpl>& schema() const;

    SubscriptionHandle::Status status() const;

    const HandleRef<UserHandleImpl>& userHandle() const;
    
    int instanceId() const;

	bool isFailOver() const;

	const bcema_SharedPtr<std::string> & requestLabel() const;

    virtual bool isValid() const;

    virtual bool isCancelPending() const;
};

inline SubscriptionHandle::SubscriptionHandle(
        CorrelationId id, 
        const HandleRef<std::string>& topicString,
		const std::string& subscriptionString,
		const bcema_SharedPtr<std::string> & requestLabel_p,
        const HandleRef<UserHandleImpl> &userHandle,
        int instanceId)
: d_topicString(topicString)
, d_subscriptionString(subscriptionString)
, d_correlationId(id)
, d_requestLabel_p(requestLabel_p)
, d_handle(0)
, d_status(UNSUBSCRIBED)
, d_userHandle_sp(userHandle)
, d_instanceId(0)
, d_isFailOver(false)
{
}

// MANIUPLATORS
inline void SubscriptionHandle::setHandle(Int64 handle)
{
    d_handle = handle;
}

inline void SubscriptionHandle::setStatus(SubscriptionHandle::Status status)
{
    d_status = status;
}

inline void SubscriptionHandle::setFailOver(bool isFailOver)
{
    d_isFailOver = isFailOver;
}

inline void SubscriptionHandle::setSchema(
        const bcema_SharedPtr<const SchemaTypeDefImpl>& schema)
{
    d_schema_sp = schema;
}

inline void SubscriptionHandle::setService(
        const HandleRef<const ServiceImpl>& schema)
{
    d_service_sp = schema;
}

// ACCESSORS
inline const CorrelationId& SubscriptionHandle::correlationId() const
{
    return d_correlationId;
}

inline const HandleRef<std::string>& SubscriptionHandle::topicString() const
{
    return d_topicString;
}

inline const std::string& SubscriptionHandle::subscriptionString() const
{
    return d_subscriptionString;
}

inline bool SubscriptionHandle::isFailOver() const
{
    return d_isFailOver;
}

inline Int64 SubscriptionHandle::handle() const
{
    return d_handle;
}

inline const bcema_SharedPtr<const SchemaTypeDefImpl>& SubscriptionHandle::schema() const
{
    return d_schema_sp;
}

inline const HandleRef<const ServiceImpl>& SubscriptionHandle::service() const
{
    return d_service_sp;
}

inline SubscriptionHandle::Status SubscriptionHandle::status() const
{
    return d_status;
}

inline const HandleRef<UserHandleImpl>& SubscriptionHandle::userHandle() const
{
    return d_userHandle_sp;
}

inline int SubscriptionHandle::instanceId() const
{
    return d_instanceId;
}

inline bool SubscriptionHandle::isValid() const
{
    return d_status != CANCELLED;
}

inline bool SubscriptionHandle::isCancelPending() const
{
    return d_status == PENDING_CANCELLATION;
}

inline const bcema_SharedPtr<std::string> & SubscriptionHandle::requestLabel() const
{
	return d_requestLabel_p;
}
} // namespace BloombergLP {
} // namespace blpapi {

#endif // #ifndef INCLUDED_BLPAPI_SUBSCRIPTIONHANDLE_H

