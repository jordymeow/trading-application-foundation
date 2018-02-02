#ifndef INCLUDED_BLPAPI_FTBL
#define INCLUDED_BLPAPI_FTBL

#include <blpapi_defs.h>
#include <blpapi_versioninfo.h>

#ifdef __cplusplus

#ifndef BLPAPI_MIN_VERSION
#define BLPAPI_MIN_VERSION BLPAPI_SDK_VERSION
#endif

#ifndef BLPAPI_TARGET_VERSION
#define BLPAPI_TARGET_VERSION BLPAPI_SDK_VERSION
#endif

#if BLPAPI_MIN_VERSION > BLPAPI_TARGET_VERSION
#error "Min required version cannot be greater than target version"
#endif

extern "C" {

// Forward declarations
typedef void* blpapi_SchemaTypeDefinition_t;

struct blpapi_Element;
typedef struct blpapi_Element blpapi_Element_t;

struct blpapi_Name;
typedef struct blpapi_Name blpapi_Name_t;
// End Forward declarations

// Function dispatch table declaration
typedef struct blpapi_FunctionEntries {
#if BLPAPI_TARGET_VERSION >= BLPAPI_MAKE_VERSION(3, 2, 3)
    size_t (*blpapi_SchemaTypeDefinition_numElementDefinitions)(
        const blpapi_SchemaTypeDefinition_t *type);
#endif // 3.2.3

#if BLPAPI_TARGET_VERSION >= BLPAPI_MAKE_VERSION(3, 2, 5)
    int (*blpapi_Element_hasElementEx)(const blpapi_Element_t *field,
        const char* nameString, const blpapi_Name_t *name,
        int excludeNullElements, int reserved);
#endif // 3.2.5
} blpapi_FunctionEntries_t;

#ifdef BLPAPI_BUILD
BLPAPI_EXPORT extern size_t                   g_blpapiFunctionTableSize;
BLPAPI_EXPORT extern blpapi_FunctionEntries_t g_blpapiFunctionEntries;
#endif

} // extern "C"

// Macros defining min version function table size
#if BLPAPI_MIN_VERSION >= BLPAPI_MAKE_VERSION(3, 2, 5)
    #define BLPAPI_MIN_VERSION_FTBL_SIZE 8
#elif BLPAPI_MIN_VERSION >= BLPAPI_MAKE_VERSION(3, 2, 3)
    #define BLPAPI_MIN_VERSION_FTBL_SIZE 4
#else
    #define BLPAPI_MIN_VERSION_FTBL_SIZE 0
#endif // BLPAPI_MIN_VERSION check

#endif // __cplusplus

#endif // INCLUDED_BLPAPI_FTBL

