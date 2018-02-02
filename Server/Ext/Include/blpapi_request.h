#ifndef INCLUDED_API_REQUEST
#define INCLUDED_API_REQUEST

#include <blpapi_types.h>
#include <blpapi_element.h>
#include <blpapi_exception.h>
#include <blpapi_defs.h>

struct blpapi_Request;
typedef struct blpapi_Request blpapi_Request_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
void blpapi_Request_destroy(
        blpapi_Request_t *request);

BLPAPI_EXPORT
blpapi_Element_t* blpapi_Request_elements(
        blpapi_Request_t *request);

#ifdef __cplusplus 
}

#include <iosfwd>

namespace BloombergLP {
namespace blpapi {

// FORWARD DECLARATION
class RequestRef;

                    // =============
                    // class Request
                    // =============

class Request {
    blpapi_Request_t *d_handle;
    Element           d_elements;

    // EXPLICITLY DISABLED 
    Request& operator=(const Request& rhs);

  public:
    // CREATORS/DESTRUCTORS
     explicit Request(blpapi_Request_t *handle); 

     Request(RequestRef ref);
     Request(Request &src); 
        // Requests have destructive copy semantics.

    ~Request();
        // Destroy the request object.
    
    // MANIPULATORS
    operator RequestRef();

    void set(const char* name, bool value);
    void set(const char* name, char value);
    void set(const char* name, Int32 value);
    void set(const char* name, Int64 value);
    void set(const char* name, Float32 value);
    void set(const char* name, Float64 value);
    void set(const char* name, const Datetime& value);
    void set(const char* name, const char* value);
    void set(const Name& name, bool value);
    void set(const Name& name, char value);
    void set(const Name& name, Int32 value);
    void set(const Name& name, Int64 value);
    void set(const Name& name, Float32 value);
    void set(const Name& name, Float64 value);
    void set(const Name& name, const Datetime& value);
    void set(const Name& name, const char* value);
        // Set the element of this request having the specified 'name' to the
        // specified 'value'.  Throw exception if an element having the
        // specified 'name' does not exist in the request, or if the specified
        // 'value' is either invalid, or incompatible with the referenced element.

    void append(const char* name, bool value);
    void append(const char* name, char value);
    void append(const char* name, Int32 value);
    void append(const char* name, Int64 value);
    void append(const char* name, Float32 value);
    void append(const char* name, Float64 value);
    void append(const char* name, const Datetime& value);
    void append(const char* name, const char* value);
    void append(const Name& name, bool value);
    void append(const Name& name, char value);
    void append(const Name& name, Int32 value);
    void append(const Name& name, Int64 value);
    void append(const Name& name, Float32 value);
    void append(const Name& name, Float64 value);
    void append(const Name& name, const Datetime& value);
    void append(const Name& name, const char* value);
        // Append the specified 'value' to the request element having the
        // specified 'name'.  Throw exception if no element named 'name' exists
        // in this request, or 'value' is not a valid value, or if the named
        // element is not of array type.

    // ACCESSORS
    Element asElement();
        // Return the modifiable top level element of this request which
        // contains all sub-elements of this request.

    Element getElement(const char* name);
    Element getElement(const Name& name);
        // Return the request element having the specified 'name'. Throw
        // exception if no such element exists in this request.

    // ACCESSORS
    const Element getElement(const char* name) const;
    const Element getElement(const Name& name) const;
        // Return the element of this request having the speicified
        // 'name'.  Throw exception if this request does not contain an element
        // having the specified 'name'.

    const Element asElement() const;
        // Return the non-modifiable top level element of this request which
        // contains all sub-elements of this request.

    blpapi_Request_t* handle() const;
        // Return the return the underlying API handle associated with this
        // request.

    std::ostream& print(std::ostream& stream,
                        int level=0, 
                        int spacesPerLevel=4) const; 
        // Format this object to the specified output 'stream' at the
        // optionally specified indentation 'level' and return a reference to
        // the modifiable 'stream'.  If 'level' is specified, optionally
        // specify 'spacesPerLevel', the number of spaces per indentation level
        // for this and all of its nested objects.  Each line is indented by
        // the absolute value of 'level * spacesPerLevel'.  If 'level' is
        // negative, suppress indentation of the first line.  If
        // 'spacesPerLevel' is negative, suppress line breaks and format the
        // entire output on one line.  If 'stream' is initially invalid, this
        // operation has no effect.  Note that a trailing newline is provided
        // in multiline mode only.
};

std::ostream& operator<<(std::ostream& stream, const Request &request);
    // Format the specified 'request' to the specified output 'stream' and
    // return a reference to the modifiable 'stream'. Note that no indentation
    // or line breaks are added.  See 'Request::print'.

                    // ================
                    // class RequestRef
                    // ================

class RequestRef {
    // This class holds a request reference, returned by the implicit
    // conversion operator in the class 'Request'. This class is used
    // to allow the construction of temporary request objects (since
    // temporaries cannot be passed by modifiable reference).

    Request *d_request_p;

public:
    RequestRef(Request *request_p);
    Request* ptr() const;
    Request* operator ->() const;
};

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

                    // =============
                    // class Request
                    // =============

inline Request::Request(blpapi_Request_t *handle)
{
    d_handle = handle;
    if (handle) {
        d_elements.rebind(blpapi_Request_elements(handle));
    }
}

inline Request::Request(RequestRef ref)
{
    Request *src = ref.ptr();
    d_handle = src->d_handle;
    d_elements = src->d_elements;
    src->d_handle = 0;
    src->d_elements.rebind(0);
}

inline Request::Request(Request &src)
{
    d_handle = src.d_handle;
    d_elements = src.d_elements;
    src.d_handle = 0;
    src.d_elements.rebind(0);
}

inline Request::~Request()
{
    if (d_handle) blpapi_Request_destroy(d_handle);
}

inline Request::operator RequestRef()
{
    return this;
}

inline void Request::set(const char* element, bool value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, char value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, Int32 value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, Int64 value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, Float32 value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, Float64 value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, const Datetime& value)
{
    d_elements.setElement(element, value);    
}

inline void Request::set(const char* element, const char* value)
{
    d_elements.setElement(element, value);    
}

inline void Request::append(const char* element, bool value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, char value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, Int32 value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, Int64 value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, Float32 value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, Float64 value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, const Datetime& value)
{
    d_elements.getElement(element).appendValue(value);    
}

inline void Request::append(const char* element, const char* value)
{
    d_elements.getElement(element).appendValue(value);    
}

/*
inline void Request::set(const unsigned char* element, const char* value)
{
    d_elements.setElement(element, value);    
}
*/

inline void Request::set(const Name& element, bool value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, char value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Int32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Int64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Float32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Float64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, const Datetime& value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, const char* value)
{
    d_elements.setElement(element, value);
}

inline void Request::append(const Name& element, bool value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, char value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, Int32 value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, Int64 value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, Float32 value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, Float64 value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, const Datetime& value)
{
    d_elements.getElement(element).appendValue(value);
}

inline void Request::append(const Name& element, const char* value)
{
    d_elements.getElement(element).appendValue(value);
}


inline Element Request::getElement(const char* name)
{
    return d_elements.getElement(name);
}

inline Element Request::getElement(const Name& name)
{
    return d_elements.getElement(name);
}

inline Element Request::asElement()
{
    return d_elements;
}

// ACCESSORS
inline const Element Request::getElement(const char* name) const
{
    return d_elements.getElement(name);
}

inline const Element Request::getElement(const Name& name) const
{
    return d_elements.getElement(name);
}

inline const Element Request::asElement() const
{
    return d_elements;
}

inline blpapi_Request_t* Request::handle() const
{
    return d_handle;
}

inline std::ostream& Request::print(
        std::ostream& stream,
        int level, 
        int spacesPerLevel) const
{
    return d_elements.print(stream, level, spacesPerLevel);
}

inline std::ostream& operator<<(std::ostream& stream, const Request &request)
{
    return request.print(stream, 0,-1);
}

                    // ================
                    // class RequestRef
                    // ================

inline RequestRef::RequestRef(Request *request)
: d_request_p(request)
{
}

inline Request* RequestRef::ptr() const
{
    return this->d_request_p;
}

inline Request* RequestRef::operator->() const
{
    return this->d_request_p;
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus 

#endif // #ifndef INCLUDED_API_REQUEST

// ---------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2008
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ---------------------------------
