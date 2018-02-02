/* blpapi_exception.h     -*-C++-*- */

#ifndef INCLUDED_BLPAPI_EXCEPTION
#define INCLUDED_BLPAPI_EXCEPTION

#include <blpapi_defs.h>
#include <blpapi_error.h>

#ifdef __cplusplus
extern "C" {
#endif

struct blpapi_ErrorInfo {
    int   exceptionClass;
    char  description[256];
};

typedef struct blpapi_ErrorInfo blpapi_ErrorInfo_t; 

BLPAPI_EXPORT
int blpapi_getErrorInfo(blpapi_ErrorInfo_t *buffer, int errorCode);


#ifdef __cplusplus
} // extern "C"


#include <string>

namespace BloombergLP {
namespace blpapi {


class Exception {
    std::string d_description;
  public:
    Exception(const std::string description)
    : d_description(description) {}

    const std::string& description() const 
    {
        return d_description;
    }
};

class InvalidStateException: public Exception {
  public:
    InvalidStateException(const std::string &description) 
    : Exception(description) {};
};

class InvalidArgumentException: public Exception {
  public:
    InvalidArgumentException(const std::string &description)
    : Exception(description) {};
};

class InvalidConverstionException: public Exception {
  public:
    InvalidConverstionException(const std::string &description)
    : Exception(description) {};
};

class IndexOutOfRangeException: public Exception {
  public:
    IndexOutOfRangeException(const std::string& description)
    : Exception(description) {};
};

class FieldNotFoundException: public Exception {
  public:
    FieldNotFoundException(const std::string& description)
    : Exception(description) {};
};

class UnknownErrorException: public Exception {
  public:
    UnknownErrorException(const std::string& description)
    : Exception(description) {};
};

class UnsupportedOperationException: public Exception {
public:
    UnsupportedOperationException(const std::string& description)
        : Exception(description) { };
};


class ExceptionUtil {  
  public:
    enum ExceptionClass {
        INVALID_STATE_CLASS = 1
      , INVALID_ARG_CLASS = 2
      , INVALID_CONVERSION_CLASS = 3
      , INDEX_OUT_OF_RANGE_CLASS = 4  
      , FIELD_NOT_FOUND_CLASS = 5
    }; 
     
  private:
    static void throwException(int errorCode)
    {
        const char* description = blpapi_getLastErrorDescription(errorCode);
        if (!description) description = "Unknown";

        switch(BLPAPI_RESULTCLASS(errorCode)) {
          case BLPAPI_INVALIDSTATE_CLASS:
              throw InvalidStateException(description);
          case BLPAPI_INVALIDARG_CLASS: 
              throw InvalidArgumentException(description);
          case BLPAPI_CNVERROR_CLASS:
              throw InvalidConverstionException(description);
          case BLPAPI_BOUNDSERROR_CLASS: 
              throw IndexOutOfRangeException(description);
          case BLPAPI_FLDNOTFOUND_CLASS: 
              throw FieldNotFoundException(description);
          default:
              throw Exception(description);
        };
    }
      
  public:
    static void throwOnError(int errorCode);  
};


inline void ExceptionUtil::throwOnError(int errorCode)
{   
    if (errorCode) throwException(errorCode);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif

#endif // #ifndef INCLUDED_BLPAPI_EXCEPTION

