#ifndef INCLUDED_API_SERVICE
#define INCLUDED_API_SERVICE

#include <blpapi_defs.h>
#include <blpapi_schema.h>
#include <blpapi_request.h>
#include <blpapi_call.h>

struct blpapi_Service;
typedef struct blpapi_Service blpapi_Service_t; 

struct blpapi_Operation;
typedef struct blpapi_Operation blpapi_Operation_t; 

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
const char* blpapi_Operation_name(
        blpapi_Operation_t *service);

BLPAPI_EXPORT
const char* blpapi_Operation_description(
        blpapi_Operation_t *service);

BLPAPI_EXPORT
int blpapi_Operation_requestDefinition(
        blpapi_Operation_t *service,
        blpapi_SchemaElementDefinition_t **requestDefinition);

BLPAPI_EXPORT
int blpapi_Operation_numResponseDefinitions(
        blpapi_Operation_t *service);

BLPAPI_EXPORT
int blpapi_Operation_responseDefinition(
        blpapi_Operation_t *service,
        blpapi_SchemaElementDefinition_t **responseDefinition,
        size_t index);

BLPAPI_EXPORT
const char* blpapi_Service_name(blpapi_Service_t *service);

BLPAPI_EXPORT
const char* blpapi_Service_description(blpapi_Service_t *service);

BLPAPI_EXPORT
int blpapi_Service_numOperations(blpapi_Service_t *service);

BLPAPI_EXPORT
int blpapi_Service_numEventDefinitions(blpapi_Service_t *service);

BLPAPI_EXPORT
int blpapi_Service_addRef(blpapi_Service_t *service);

BLPAPI_EXPORT
void blpapi_Service_release(blpapi_Service_t *service);

BLPAPI_EXPORT
const char* blpapi_Service_authorizationServiceName(
        blpapi_Service_t *service);

BLPAPI_EXPORT
int blpapi_Service_getOperation(
        blpapi_Service_t *service,
        blpapi_Operation_t **operation,
        const char* nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Service_getOperationAt(
        blpapi_Service_t *service,
        blpapi_Operation_t **operation,
        size_t index);

BLPAPI_EXPORT
int blpapi_Service_getEventDefinition(
        blpapi_Service_t *service,
        blpapi_SchemaElementDefinition_t **result,
        const char* nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Service_getEventDefinitionAt(
        blpapi_Service_t *service,
        blpapi_SchemaElementDefinition_t **result,
        size_t index);

BLPAPI_EXPORT
int blpapi_Service_createRequest(
        blpapi_Service_t* service,
        blpapi_Request_t** request,
        const char *operation);
        
BLPAPI_EXPORT
int blpapi_Service_createAuthorizationRequest(
        blpapi_Service_t* service,
        blpapi_Request_t** request,
        const char *operation);

#ifdef __cplusplus 
}

#include <blpapi_exception.h>

namespace BloombergLP {
namespace blpapi {

class Operation {
    blpapi_Operation_t *d_handle;

  public:
    // CREATORS
    Operation(blpapi_Operation_t *handle);

    ~Operation();

    // ACCESSORS
    const char* name() const;
        // Return a non-modifiable pointer to the name of the operation.  Note
        // that the return pointer is only valid while this object remains
        // valid.

    const char* description() const;
        // Return a non-modifiable pointer to the description of this operation.
        // Note that the return pointer is only valid while this object remains
        // valid.

    SchemaElementDefinition requestDefinition() const;
        // Return the schema type definition that defines the properties of this
        // opeartion. 

    int numResponseDefinitions() const;
        // Return the number of the response types that can be returned by this
        // operation.

    SchemaElementDefinition responseDefinition(size_t index) const;
        // Return the schema type definition that defines the properties of the
        // the 'index'th possible response type that can be returned by this
        // operation.  Throw exception of index >= 'numResponseTypes()'.

    blpapi_Operation_t* handle() const;

    bool isValid() const;
};

class Service {
    blpapi_Service_t *d_handle;

    void addRef();
    void release();

public:
    // CREATORS
    Service();

    Service(blpapi_Service_t *handle);

    Service(const Service& src);

    ~Service();

    // MANIPULATORS
    Request createRequest(const char* operation) const;

    Request createAuthorizationRequest(const char* authorizationOperation=0) const;
   
    Service& operator=(const Service& rhs);

    // ACCESSORS
    const char* name() const;
        // Return a non-modifiable pointer to name of this service.  Note that
        // the return pointer is only valid as long as this service object
        // remains valid.

    const char* description() const;
        // Return a non-modifiable pointer to the description of this service.
        // Note that the return pointer is only valid as long as this service
        // object remains valid.

    size_t numOperations() const;
        // Return the number of operations defined by this service object.

    bool hasOperation(const char* name) const;

	bool hasOperation(const Name& name) const;

    Operation getOperation(size_t index) const;
        // Return the definition of the  'index'th operation defined by this
        // service.  Throw exception if 'index' >= 'numOperations()'.

    Operation getOperation(const char* name) const;
        // Return the definition of the operation having the specified 'name'.
        // Throw exception if no such operation exists in this service. 

	Operation getOperation(const Name& name) const;
        // Return the definition of the operation having the specified 'name'.
        // Throw exception if no such operation exists in this service. 

    int numEventDefinitions() const;
        // Return the number of unsolicited messages defined by this service.


    bool hasEventDefinition(const char* name) const;

	bool hasEventDefinition(const Name& name) const;

    SchemaElementDefinition getEventDefinition(size_t index) const;
        // Return the definition of the 'index'th unsolicited message defined by
        // this service.  Throw exception if index >= 'numEventDefinitions()'.

    SchemaElementDefinition getEventDefinition(const char* name) const;
        // Return the definition of the unsolicited message having the specified
        // 'name' defined by this service.  Throw exception of the no
        // unsolicited message having the specified 'name' is defined by this
        // service.

	SchemaElementDefinition getEventDefinition(const Name& name) const;
        // Return the definition of the unsolicited message having the specified
        // 'name' defined by this service.  Throw exception of the no
        // unsolicited message having the specified 'name' is defined by this
        // service.

    const char* authorizationServiceName() const;
        // Return the name of the service for which an authorization must be
        // established in order to access restricted operations on this service.  
        // Return and empty string if no authorization is request to access operations
        // on this service.

    blpapi_Service_t* handle() const;
        // Return the API handle associated witht his service object.

	bool isValid() const;
		// Returns true if this service is valid false otherwise
};

                //=======================
                // class Operation
                //=======================


inline Operation::Operation(blpapi_Operation_t *handle)
: d_handle(handle)
{
}

inline Operation::~Operation()
{
}

inline const char* Operation::name() const
{
    return blpapi_Operation_name(d_handle);
}

inline const char* Operation::description() const
{
    return blpapi_Operation_description(d_handle);
}

inline SchemaElementDefinition Operation::requestDefinition() const
{
    blpapi_SchemaElementDefinition_t *definition;

    ExceptionUtil::throwOnError(
            blpapi_Operation_requestDefinition(d_handle, &definition));
    return SchemaElementDefinition(definition);
}

inline int Operation::numResponseDefinitions() const
{
    return blpapi_Operation_numResponseDefinitions(d_handle);
}

inline SchemaElementDefinition Operation::responseDefinition(size_t index) const
{
    blpapi_SchemaElementDefinition_t *definition;

    ExceptionUtil::throwOnError(
            blpapi_Operation_responseDefinition(d_handle, &definition, index));
    return SchemaElementDefinition(definition);
}

inline blpapi_Operation_t* Operation::handle() const
{
    return d_handle;
}

inline bool Operation::isValid() const
{
    return d_handle != 0;
}

                //==============
                // class Service
                //==============

inline Service::Service()
: d_handle(0)
{
}

inline Service::Service(const Service& src)
    : d_handle(src.d_handle)
{
    addRef();
}

inline Service::Service(blpapi_Service_t *handle)
    : d_handle(handle)
{
    addRef();
}

inline Service::~Service()
{
    release();
}

inline Service& Service::operator=(const Service& rhs)
{
    release();

    d_handle = rhs.d_handle;
    addRef();

    return *this;
}

inline void Service::addRef()
{
    if (d_handle) 
        blpapi_Service_addRef(d_handle);    
}

inline void Service::release()
{
    if (d_handle)
        blpapi_Service_release(d_handle);        
}

inline Request Service::createRequest(const char* operation) const
{
    blpapi_Request_t *request;
    ExceptionUtil::throwOnError(
            blpapi_Service_createRequest(
                d_handle,
                &request,
                operation)
            );
    return Request(request);
}

inline Request Service::createAuthorizationRequest(
        const char* authorizationOperation) const
{
    blpapi_Request_t *request;
    ExceptionUtil::throwOnError(
            blpapi_Service_createAuthorizationRequest(
                d_handle,
                &request,
                authorizationOperation)
            );
    return Request(request);
}

    // ACCESSORS
inline blpapi_Service_t* Service::handle() const
{
    return d_handle;
}

inline bool Service::isValid() const
{
	return (d_handle != 0);
}

inline const char* Service::name() const
{
    return blpapi_Service_name(d_handle);
}


inline const char* Service::description() const
{
    return blpapi_Service_description(d_handle);
}


inline size_t Service::numOperations() const
{
    return blpapi_Service_numOperations(d_handle);
}

inline bool Service::hasOperation(const char* name) const
{
    blpapi_Operation_t *operation;
    if (blpapi_Service_getOperation(d_handle, &operation, name, 0))
       return false;
    else 
        return true;
}

inline bool Service::hasOperation(const Name& name) const
{
    blpapi_Operation_t *operation;
    if (blpapi_Service_getOperation(d_handle, &operation, 0, name.impl()))
       return false;
    else 
        return true;
}

inline Operation Service::getOperation(size_t index) const
{
    blpapi_Operation_t *operation;
    ExceptionUtil::throwOnError(
            blpapi_Service_getOperationAt(d_handle, &operation, index));
    return operation;
}

inline Operation Service::getOperation(const char* name) const
{
    blpapi_Operation_t *operation;
    ExceptionUtil::throwOnError(
            blpapi_Service_getOperation(d_handle, &operation, name, 0));
    return operation;
}

inline Operation Service::getOperation(const Name& name) const
{
    blpapi_Operation_t *operation;
    ExceptionUtil::throwOnError(
            blpapi_Service_getOperation(d_handle, &operation, 0, name.impl()));
    return operation;
}

inline int Service::numEventDefinitions() const
{
    return blpapi_Service_numEventDefinitions(d_handle);
}


inline bool Service::hasEventDefinition(const char* name) const
{
    blpapi_SchemaElementDefinition_t *eventDefinition;

    return blpapi_Service_getEventDefinition(
            d_handle, &eventDefinition, name, 0) == 0 ? true : false;
}

inline bool Service::hasEventDefinition(const Name& name) const
{
    blpapi_SchemaElementDefinition_t *eventDefinition;

    return blpapi_Service_getEventDefinition(
            d_handle, &eventDefinition, 0, name.impl()) == 0 ? true : false;
}


inline SchemaElementDefinition Service::getEventDefinition(size_t index) const
{
    blpapi_SchemaElementDefinition_t *eventDefinition;

    ExceptionUtil::throwOnError(
            blpapi_Service_getEventDefinitionAt(
                d_handle, &eventDefinition, index));
    return SchemaElementDefinition(eventDefinition);
}


inline SchemaElementDefinition Service::getEventDefinition(const char* name) const
{
    blpapi_SchemaElementDefinition_t *eventDefinition;
    ExceptionUtil::throwOnError(
            blpapi_Service_getEventDefinition(
                d_handle, &eventDefinition, name, 0));
    return SchemaElementDefinition(eventDefinition);
}

inline SchemaElementDefinition Service::getEventDefinition(const Name& name) const
{
    blpapi_SchemaElementDefinition_t *eventDefinition;
    ExceptionUtil::throwOnError(
            blpapi_Service_getEventDefinition(
                d_handle, &eventDefinition, 0, name.impl()));
    return SchemaElementDefinition(eventDefinition);
}

inline const char* Service::authorizationServiceName() const
{
    return blpapi_Service_authorizationServiceName(d_handle);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif /* ifdef __cplusplus  */

#endif /* #ifndef INCLUDED_API_SERVICE */

