// blpapi_name.h     -*-C++-*-

#ifndef INCLUDED_BLPAPI_NAME
#define INCLUDED_BLPAPI_NAME

#include <blpapi_types.h>
#include <stddef.h>
#include <blpapi_defs.h>

struct blpapi_Name;
typedef struct blpapi_Name blpapi_Name_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Name_t* blpapi_Name_create(
        const char* nameString);

BLPAPI_EXPORT
void blpapi_Name_destroy(
        blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_Name_duplicate(
        const blpapi_Name_t *src);

BLPAPI_EXPORT
int blpapi_Name_equalsStr(
        const blpapi_Name_t *name, 
        const char *string);

BLPAPI_EXPORT
const char* blpapi_Name_string(
        const blpapi_Name_t *name);

BLPAPI_EXPORT
size_t blpapi_Name_length(
        const blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_Name_findName(
        const char* nameString);

#ifdef __cplusplus 
}

#include <algorithm> // for swap
#include <iostream>
#include <cstring>   // for strcmp

namespace BloombergLP {
namespace blpapi {


                         // ==========
                         // class Name
                         // ==========
class Name {
    blpapi_Name_t *d_impl_p;

  public:
    // CREATORS
    Name();
        // Construct an unitialized name constant.

    Name(blpapi_Name_t *handle);

    Name(const Name& original);

    explicit Name(const char* nameString);    

    ~Name();

    // MANIPULATORS
    Name& operator=(const Name& rhs);

    // ACCESSORS
    const char *string() const;

    size_t length() const;

    blpapi_Name_t* impl() const;

    static Name findName(const char* nameString);

    static bool hasName(const char* nameString);
};

// FREE OPERATORS
inline
bool operator==(const Name& lhs, const Name& rhs);
    // Return true if the specified 'lhs' and 'rhs' name objects have the same value,
    // and false otherwise.  Two 'Name' objects have the same value
    // if and only if their 

inline
bool operator==(const Name& lhs, const char* rhs);
    // Return true if the specified 'lhs' and 'rhs' name objects have the same value,
    // and false otherwise.  Two 'Name' objects have the same value
    // if and only if their 
inline
bool operator!=(const Name& lhr, const Name& rhs);
    // Return true if the specified 'lhs' and 'rhs' objects do not have the same
    // value, and false otherwise. 

inline
bool operator<(const Name& lhs, const Name& rhs);
	// Return < 0 if lhs < rhs, 0 if lhs == rhs, > 0 if lhs > rhs

#if 0
inline
std::ostream& operator<<(std::ostream&            output,
                         const Name& address);
    // Write the specified IPv4 'address' value to the specified 'output'
    // stream in the format of address:portNumber, e.g., "127.0.0.1:5".

#endif

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

// CREATORS
inline Name::Name(blpapi_Name_t *handle)
: d_impl_p(handle)
{
}

inline Name::Name()
: d_impl_p(0)
{
}

inline Name::Name(const Name& original)
: d_impl_p(blpapi_Name_duplicate(original.d_impl_p))
{
}

inline Name::Name(const char* nameString)
{
    d_impl_p = blpapi_Name_create(nameString);
}

inline Name::~Name()
{
    if (d_impl_p) blpapi_Name_destroy(d_impl_p);
}

// MANIPULATORS
inline Name& Name::operator=(const Name& rhs)
{
    if (&rhs != this) {
        Name tmp(rhs);
        std::swap(tmp.d_impl_p, d_impl_p);
    }
    return *this;
}

// ACCESSORS
inline const char* Name::string() const
{
    return blpapi_Name_string(d_impl_p);
}

inline size_t Name::length() const
{
    return blpapi_Name_length(d_impl_p);
}

inline blpapi_Name_t* Name::impl() const
{
    return d_impl_p;
}

inline Name Name::findName(const char* nameString)
{
    return Name(blpapi_Name_findName(nameString));
}

inline bool Name::hasName(const char* nameString)
{
    return blpapi_Name_findName(nameString) ? true : false;
}

// FREE OPERATORS
inline
bool operator==(const Name& lhs, const Name& rhs)
{
    return (lhs.impl() == rhs.impl());
}

inline
bool operator==(const Name& lhs, const char* rhs)
{
    return blpapi_Name_equalsStr(lhs.impl(), rhs) != 0;
}

inline
bool operator!=(const Name& lhs, const Name& rhs)
{
    return !(lhs == rhs);
}

inline
bool operator<(const Name& lhs, const Name& rhs)
{
	return std::strcmp(lhs.string(), rhs.string()) < 0;
}

inline
std::ostream& operator<<(std::ostream& stream,
                         const Name& name)
{
    stream << name.string();
    return stream;
}


} // namespace blpapi {
} // namespace BloombergLP {

#endif // __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_NAME

