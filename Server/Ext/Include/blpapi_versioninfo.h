#ifndef _INCLUDED_BLOOMBERGLP_BLPAPI_VERSIONINFO
#define _INCLUDED_BLOOMBERGLP_BLPAPI_VERSIONINFO

#include <blpapi_defs.h>

#define BLPAPI_MAKE_VERSION(MAJOR, MINOR, PATCH) ((MAJOR) * 10000 + \
                                                  (MINOR) * 100 + \
                                                  (PATCH))

#define BLPAPI_SDK_VERSION  BLPAPI_MAKE_VERSION(3, 2, 9)

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
void blpapi_getVersionInfo(int *majorVersion,
                           int *minorVersion,
                           int *patchVersion,
                           int *buildVersion);
#ifdef __cplusplus 
}

namespace BloombergLP {
namespace blpapi {

class VersionInfo {
    int d_major;
    int d_minor;
    int d_patch;
    int d_build;

public:
    // CREATORS
    VersionInfo();

	// ACCESSORS
    int majorVersion() const;
    int minorVersion() const;
    int patchVersion() const;
    int buildVersion() const;
};

inline VersionInfo::VersionInfo()
{
    blpapi_getVersionInfo(&d_major, &d_minor, &d_patch, &d_build);
}

inline int VersionInfo::majorVersion() const
{
    return d_major;
}

inline int VersionInfo::minorVersion() const
{
    return d_minor;
}

inline int VersionInfo::patchVersion() const
{
    return d_patch;
}

inline int VersionInfo::buildVersion() const
{
    return d_build;
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif /* ifdef __cplusplus  */

#endif /* _INCLUDED_BLOOMBERGLP_BLPAPI_VERSIONINFO */

