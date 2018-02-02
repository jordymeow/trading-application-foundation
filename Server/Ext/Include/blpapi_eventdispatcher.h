// blpapi_eventdispatcher.h     -*-C++-*-

#ifndef INCLUDED_API_EVENTDISPATCHER
#define INCLUDED_API_EVENTDISPATCHER

#include <blpapi_defs.h>
#include <stddef.h> /* for size_t */

#ifdef __cplusplus 
extern "C" {
#endif

struct blpapi_EventDispatcher;
typedef struct blpapi_EventDispatcher blpapi_EventDispatcher_t;

BLPAPI_EXPORT
blpapi_EventDispatcher_t* blpapi_EventDispatcher_create(
        size_t numDispatcherThreads);

BLPAPI_EXPORT
void blpapi_EventDispatcher_destroy(blpapi_EventDispatcher_t *handle);

BLPAPI_EXPORT
int blpapi_EventDispatcher_start(blpapi_EventDispatcher_t *handle);

BLPAPI_EXPORT
int blpapi_EventDispatcher_stop(blpapi_EventDispatcher_t *handle,
                                int async);

BLPAPI_EXPORT
int blpapi_EventDispatcher_dispatchEvents(blpapi_EventDispatcher_t *handle);

#ifdef __cplusplus 
} // extern "C"

namespace BloombergLP {
namespace blpapi {

                         // =====================
                         // class EventDispatcher
                         // =====================
class EventDispatcher {
    blpapi_EventDispatcher_t *d_impl_p;
  public:
    EventDispatcher(size_t numDispatcherThreads=1);

    ~EventDispatcher();

    int start();

    int stop(bool async = false);

    blpapi_EventDispatcher_t*  impl() const;
};

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

                         // ---------------------
                         // class EventDispatcher
                         // ---------------------

inline EventDispatcher::EventDispatcher(size_t numDispatcherThreads)
: d_impl_p(0)
{
    d_impl_p = blpapi_EventDispatcher_create(numDispatcherThreads);
}

inline EventDispatcher::~EventDispatcher()
{
    if (d_impl_p) blpapi_EventDispatcher_destroy(d_impl_p);
}

inline int EventDispatcher::start()
{
    return blpapi_EventDispatcher_start(d_impl_p);
}

inline int EventDispatcher::stop(bool async)
{
    return blpapi_EventDispatcher_stop(d_impl_p, async);
}

inline blpapi_EventDispatcher_t*  EventDispatcher::impl() const
{
    return d_impl_p;
}


} // namespace blpapi {
} // namespace BloombergLP {

#endif /* ifdef __cplusplus  */

#endif // #ifndef INCLUDED_API_EVENTDISPATCHER

