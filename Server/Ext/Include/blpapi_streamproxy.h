// blpapi_streamproxy.h     -*-C++-*-
#ifndef INCLUDED_BLPAPI_STREAMPROXY
#define INCLUDED_BLPAPI_STREAMPROXY

typedef int(*blpapi_StreamWriter_t)(const char* data, int length, void *stream);

#ifdef __cplusplus 

#include <ostream>

namespace BloombergLP {
namespace blpapi {

static int OstreamWriter(const char* data, int length, void *stream)
{
    reinterpret_cast<std::ostream*>(stream)->write(data, length);
    return 0;
}

}
}

#endif

#endif // #ifndef INCLUDED_BLPAPI_STREAMPROXY

