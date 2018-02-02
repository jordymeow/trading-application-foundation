#ifndef INCLUDED_BLPAPI_CALL
#define INCLUDED_BLPAPI_CALL

#ifdef __cplusplus

#if defined(_WIN32) || defined(__WIN32__)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <TCHAR.h>
#endif

#include <stddef.h>

#include <blpapi_dispatchtbl.h>
#include <blpapi_exception.h>

#if defined(_WIN32) || defined(__WIN32__)
#define BLPAPI_CALL(FUNCNAME) \
    ((offsetof(blpapi_FunctionEntries_t, FUNCNAME) < \
    BLPAPI_MIN_VERSION_FTBL_SIZE) ? (FUNCNAME) : \
    (offsetof(blpapi_FunctionEntries_t, FUNCNAME) < g_blpapiFunctionTableSize - 1) ? \
    (g_functionEntries_p->FUNCNAME) : \
    (throw UnsupportedOperationException(#FUNCNAME " not supported"), \
    FUNCNAME))
#else
#define BLPAPI_CALL(FUNCNAME) (FUNCNAME)
#endif // #if defined(_WIN32) || defined(__WIN32__)

namespace BloombergLP {
namespace blpapi {

#ifndef BLPAPI_BUILD

class BlpCallInit {
public:
    BlpCallInit(blpapi_FunctionEntries_t **functionEntries_pp,
        size_t *ftblSize);
};

#define BLPAPI_CALL_INIT() \
    static blpapi_FunctionEntries_t *g_functionEntries_p = 0; \
    static size_t g_blpapiFunctionTableSize = 0; \
    static BlpCallInit g_blpCallInit(&g_functionEntries_p, \
        &g_blpapiFunctionTableSize); \

BLPAPI_CALL_INIT()

inline void blpCallInitImpl(blpapi_FunctionEntries_t** functionEntries_p,
                            size_t* ftblSize);
inline BlpCallInit::BlpCallInit(
    blpapi_FunctionEntries_t** functionEntries_p,
    size_t* ftblSize)
{
    if (*functionEntries_p == 0) {
        blpCallInitImpl(functionEntries_p, ftblSize);
    }
}

#if defined(sun) || defined(__sun)
inline void blpCallInitImpl(
    blpapi_FunctionEntries_t** functionEntries_p,
    size_t* ftblSize)
{
}
#elif defined(linux) || defined(__linux)
inline void blpCallInitImpl(
    blpapi_FunctionEntries_t** functionEntries_p,
    size_t* ftblSize)
{
}
#elif defined(_WIN32) || defined(__WIN32__)
inline void blpCallInitImpl(
    blpapi_FunctionEntries_t** functionEntries_p,
    size_t* ftblSize)
{
    HMODULE hModule = ::LoadLibraryEx(_T("blpapi32.dll"), NULL, 0);
    if (hModule == NULL) return;

    *functionEntries_p = (blpapi_FunctionEntries_t*)
        ::GetProcAddress(hModule, "g_blpapiFunctionEntries");

    size_t *ftblSize_p = (size_t*)::GetProcAddress(hModule,
        "g_blpapiFunctionTableSize");
    if (ftblSize_p != NULL) {
        *ftblSize = *ftblSize_p;
    }
}
#endif // blpCallInitImpl os specific implmentation

#else
static blpapi_FunctionEntries_t *g_functionEntries_p = 0; 
static size_t g_blpapiFunctionTableSize = 0; 

#endif // ifdef BLPAPI_BUILD

}
} // namespace BloombergLP {

#endif // __cplusplus

#endif // INCLUDED_BLPAPI_CALL
