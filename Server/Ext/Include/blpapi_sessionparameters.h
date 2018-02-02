/* blpapi_sessionparameters.h     -*-C++-*- */

#ifndef INCLUDED_BLPAPI_SESSIONPARAMETERS
#define INCLUDED_BLPAPI_SESSIONPARAMETERS

#include <blpapi_defs.h>

struct blpapi_SessionParameters;
typedef struct blpapi_SessionParameters blpapi_SessionParameters_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_SessionParameters_t* blpapi_SessionParameters_create();

BLPAPI_EXPORT
void blpapi_SessionParameters_destroy(
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionParameters_setServerHost(
        blpapi_SessionParameters_t *parameters,
        const char* serverHost);

BLPAPI_EXPORT
int blpapi_SessionParameters_setServerPort(
        blpapi_SessionParameters_t *parameters,
        unsigned short serverPort);

BLPAPI_EXPORT
int blpapi_SessionParameters_setDefaultServices(
        blpapi_SessionParameters_t *parameters,
        const char* defaultServices);

BLPAPI_EXPORT
int blpapi_SessionParameters_setDefaultSubscriptionService(
        blpapi_SessionParameters_t *parameters,
        const char* defaultSubscriptionService);

BLPAPI_EXPORT
void blpapi_SessionParameters_setDefaultTopicPrefix(
        blpapi_SessionParameters_t *parameters,
        const char* defaultTopicPrefix);

BLPAPI_EXPORT
void blpapi_SessionParameters_setAllowMultipleCorrelatorsPerMsg(
        blpapi_SessionParameters_t *parameters,
        int allowMultipleCorrelatorsPerMsg);

BLPAPI_EXPORT
const char* blpapi_SessionParameters_serverHost(
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
unsigned blpapi_SessionParameters_serverPort(
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionParameters_defaultServices(
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionParameters_defaultSubscriptionService( 
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
const char* blpapi_SessionParameters_defaultTopicPrefix( 
        blpapi_SessionParameters_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionParameters_allowMultipleCorrelatorsPerMsg( 
        blpapi_SessionParameters_t *parameters);

#ifdef __cplusplus 
}

namespace BloombergLP {
namespace blpapi {

class SessionParameters {
    blpapi_SessionParameters_t *d_handle_p;
  public:
    // CREATORS/DESTRUCTORS
    SessionParameters();

    ~SessionParameters();

    // MANIUPLATORS
    void setServerHost(const char* host);

    void setServerPort(unsigned short port);

    void setDefaultServices(const char* defaultServices);

    void setDefaultSubscriptionService(const char* defaultSubscriptionService);
    
    void setDefaultTopicPrefix(const char* defaultTopicPrefix);

    void setAllowMultipleCorrelatorsPerMsg(bool allowMultipleCorrelatorsPerMsg);

    // ACCESSOR
    const char* serverHost() const;

    unsigned serverPort() const;

    const char* defaultServices() const;

    const char* defaultSubscriptionService() const;

    const char* defaultTopicPrefix() const;

    bool allowMultipleCorrelatorsPerMsg() const;

    blpapi_SessionParameters_t* handle() const;
};

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

inline SessionParameters::SessionParameters()
{
    d_handle_p = blpapi_SessionParameters_create();
}

inline SessionParameters::~SessionParameters()
{
    blpapi_SessionParameters_destroy(d_handle_p);
}

// MANIPULATOR
inline void SessionParameters::setServerHost(const char* serverHost)
{
    blpapi_SessionParameters_setServerHost( d_handle_p, serverHost);
}

inline void SessionParameters::setServerPort(unsigned short serverPort)
{
    blpapi_SessionParameters_setServerPort( d_handle_p, serverPort);
}

inline void SessionParameters::setDefaultServices(const char* defaultServices)
{
    blpapi_SessionParameters_setDefaultServices(d_handle_p, defaultServices);
}

inline void SessionParameters::setDefaultSubscriptionService(const char* defaultSubscriptionService)
{
    blpapi_SessionParameters_setDefaultSubscriptionService(
            d_handle_p,
            defaultSubscriptionService);
}

inline void SessionParameters::setDefaultTopicPrefix(const char* defaultTopicPrefix)
{
    blpapi_SessionParameters_setDefaultTopicPrefix(
            d_handle_p,
            defaultTopicPrefix);
}

inline void SessionParameters::setAllowMultipleCorrelatorsPerMsg(bool allowMultipleCorrelatorsPerMsg)
{
    blpapi_SessionParameters_setAllowMultipleCorrelatorsPerMsg(
            d_handle_p,
            allowMultipleCorrelatorsPerMsg);
}

inline const char* SessionParameters::serverHost() const
{
    return blpapi_SessionParameters_serverHost(d_handle_p);
}

inline unsigned SessionParameters::serverPort() const
{
    return blpapi_SessionParameters_serverPort(d_handle_p);
}

inline const char* SessionParameters::defaultServices() const
{
    return blpapi_SessionParameters_defaultServices(d_handle_p);
}

inline const char* SessionParameters::defaultSubscriptionService() const
{
    return blpapi_SessionParameters_defaultSubscriptionService(d_handle_p);
}

inline const char* SessionParameters::defaultTopicPrefix() const
{
    return blpapi_SessionParameters_defaultTopicPrefix(d_handle_p);
}

inline bool SessionParameters::allowMultipleCorrelatorsPerMsg() const
{
    return blpapi_SessionParameters_allowMultipleCorrelatorsPerMsg(d_handle_p);
}

inline blpapi_SessionParameters_t* SessionParameters::handle() const
{
    return d_handle_p;
}

} // close namespace blpapi {
} // close namespace BloombergLP {

#endif // #ifdef _cplusplus

#endif // #ifndef INCLUDED_BLPAPI_SESSIONPARAMETERS

