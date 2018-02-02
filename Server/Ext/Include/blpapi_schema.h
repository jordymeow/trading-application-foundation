// blpapi_schema.h     -*-C++-*-

#ifndef INCLUDED_API_SCHEMA
#define INCLUDED_API_SCHEMA

#include <blpapi_name.h>
#include <blpapi_types.h>
#include <blpapi_constant.h>
#include <blpapi_defs.h>
#include <blpapi_streamproxy.h>

typedef void* blpapi_SchemaElementDefinition_t;
typedef void* blpapi_SchemaTypeDefinition_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Name_t* blpapi_SchemaElementDefinition_name(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
const char* blpapi_SchemaElementDefinition_description(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
int blpapi_SchemaElementDefinition_status(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_SchemaTypeDefinition_t* blpapi_SchemaElementDefinition_type(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_numAlternateNames(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_SchemaElementDefinition_getAlternateName(
        const blpapi_SchemaElementDefinition_t *field,
        size_t index);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_numNames(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_minValues(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_maxValues(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
int blpapi_SchemaElementDefinition_print(
        const blpapi_SchemaElementDefinition_t* element, 
        blpapi_StreamWriter_t streamWriter,
        void *userStream,
        int level, 
        int spacesPerLevel);

BLPAPI_EXPORT
void blpapi_SchemaElementDefinition_setUserData(
		blpapi_SchemaElementDefinition_t *field,
		void * userdata);

BLPAPI_EXPORT
void * blpapi_SchemaElementDefinition_userData(
		const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_SchemaTypeDefinition_name(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
const char* blpapi_SchemaTypeDefinition_description(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_status(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_datatype(
        const blpapi_SchemaTypeDefinition_t *type);

#ifdef __cplusplus
BLPAPI_EXPORT
bool blpapi_SchemaTypeDefinition_isComplexType(
		const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
bool blpapi_SchemaTypeDefinition_isSimpleType(
		const blpapi_SchemaTypeDefinition_t *type);	

BLPAPI_EXPORT
bool blpapi_SchemaTypeDefinition_isEnumerationType(
		const blpapi_SchemaTypeDefinition_t *type);
#endif

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isComplex(
		const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isSimple(
		const blpapi_SchemaTypeDefinition_t *type);	

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isEnumeration(
		const blpapi_SchemaTypeDefinition_t *type);


BLPAPI_EXPORT
size_t blpapi_SchemaTypeDefinition_numElementDefinitions(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
blpapi_SchemaElementDefinition_t* 
blpapi_SchemaTypeDefinition_getElementDefinition(
        const blpapi_SchemaTypeDefinition_t *type,
        const char* nameString,
        const blpapi_Name_t* name);

BLPAPI_EXPORT
blpapi_SchemaElementDefinition_t* 
blpapi_SchemaTypeDefinition_getElementDefinitionAt(
        const blpapi_SchemaTypeDefinition_t *type,
        size_t index);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_print(
        const blpapi_SchemaTypeDefinition_t* element, 
        blpapi_StreamWriter_t streamWriter,
        void *userStream,
        int level, 
        int spacesPerLevel);

BLPAPI_EXPORT
void blpapi_SchemaTypeDefinition_setUserData(
		blpapi_SchemaTypeDefinition_t *element,
		void * userdata);

BLPAPI_EXPORT
void * blpapi_SchemaTypeDefinition_userData(
		const blpapi_SchemaTypeDefinition_t *element);

BLPAPI_EXPORT
blpapi_ConstantList_t* 
blpapi_SchemaTypeDefinition_enumeration(
		const blpapi_SchemaTypeDefinition_t *element);


#ifdef __cplusplus 
}


#include <iosfwd>

namespace BloombergLP {
namespace blpapi {

struct SchemaStatus {
    enum Value {
        ACTIVE              = BLPAPI_STATUS_ACTIVE,
        DEPRECATED          = BLPAPI_STATUS_DEPRECATED,
        INACTIVE            = BLPAPI_STATUS_INACTIVE,
        PENDING_DEPRECATION = BLPAPI_STATUS_PENDING_DEPRECATION
    };
};

class SchemaTypeDefinition;

class SchemaElementDefinition{
    blpapi_SchemaElementDefinition_t *d_impl_p;
  public:
	enum {
		UNBOUNDED = BLPAPI_ELEMENTDEFINITION_UNBOUNDED
	};

    // PUBLIC TYPES
    SchemaElementDefinition(blpapi_SchemaElementDefinition_t *handle);

    ~SchemaElementDefinition();

	// MANIPULATORS
	void setUserData(void * userData);

    // ACCESSORS
    Name name() const;
    // Return the name associated with this field definition.

    const char* description() const;
    // Return the description associated with this field definition.

    int status() const;

    const SchemaTypeDefinition typeDefinition() const;

    int minValues() const;
    // Return a positive integer number indicating the minimum number
    // of values that can be assigned to a field having this definition.

    int maxValues() const ;
    // Return a positive integer number indicating the maximum number
    // of values that can be assigned to a field having this definition.
    // If 'maxValues' is greater than one, then this a field having this
    // defintion is considered to be an array type. Note that maxValues
    // cannot be zero.

    int numAlternateNames() const;

    Name getAlternateName(size_t index) const;

    std::ostream& print(std::ostream& stream,
                        int level=0, 
                        int spacesPerLevel=4) const; 

	void * userData() const;
};

class SchemaTypeDefinition {
    blpapi_SchemaTypeDefinition_t *d_impl_p;

  public:
    SchemaTypeDefinition(blpapi_SchemaTypeDefinition_t *handle);

    ~SchemaTypeDefinition();

	// MANIPULATORS
	void setUserData(void * userData);

    // ACCESSORS
    int datatype() const;
    // Return the data type associated with this type defintion.

    Name name() const;
    // Return the name of this type definition.

    const char* description() const;
    // Return a string that describes this type definition.

    int status() const;
    // Return the status of this type definition.

    int numElementDefinitions() const;
    // Retun the number of field defintions contained by this type 
    // defintion.

	bool isComplexType() const;
	// Return true if this is a sequence or choice type.

	bool isSimpleType() const;
	// Return true if this is a neither sequence nor choice type.

	bool isEnumerationType() const;
	// Return true if this is an enmeration type.

    bool hasElementDefinition(const Name& name) const;
    //  Return true if the type definition has a field having the
    //  specified 'name', and false otherwise.

    bool hasElementDefinition(const char* name) const;
    //  Return true if the type definition has a field having the
    //  specified 'name', and false otherwise.

    SchemaElementDefinition getElementDefinition(const Name& name) const;

    SchemaElementDefinition getElementDefinition(const char* nameString) const;
    
    SchemaElementDefinition getElementDefinition(size_t index) const;
    // Return the field definition at the specified 'index' in this 
    // type definition if this type definition is a complex type that
    // contains fields.  Throw exception if 'index' is >=
    // 'numElementsDefinitions()'.

    const ConstantList enumeration() const;
    // Return a list of constants associated with this type definition if
    // this definition is an 'ENUMERATION' type.  Return an empty list 
    // otherwise.
    
    std::ostream& print(std::ostream& stream,
                        int level=0, 
                        int spacesPerLevel=4) const; 

	void * userData() const;
};



// INLINE FUNCTION DEFINITIONS


              // ------------------
              // SchemaElementDefinition
              // ------------------

inline SchemaElementDefinition::SchemaElementDefinition(
    blpapi_SchemaElementDefinition_t *handle)
: d_impl_p(handle)
{
}


inline SchemaElementDefinition::~SchemaElementDefinition()
{
}

inline Name SchemaElementDefinition::name() const
{
    return Name(blpapi_SchemaElementDefinition_name(d_impl_p));
}

#if 0 // TODO Implement
    const char* description() const;
    int status() const;
#endif

inline const SchemaTypeDefinition SchemaElementDefinition::typeDefinition() const
{
	return blpapi_SchemaElementDefinition_type(d_impl_p);
}

inline int SchemaElementDefinition::minValues() const
{
    return blpapi_SchemaElementDefinition_minValues(d_impl_p);
}

inline int SchemaElementDefinition::maxValues() const
{
    return blpapi_SchemaElementDefinition_maxValues(d_impl_p);
}

inline int SchemaElementDefinition::numAlternateNames() const
{
    return blpapi_SchemaElementDefinition_numAlternateNames(d_impl_p);
}

inline Name SchemaElementDefinition::getAlternateName(size_t index) const
{
    return blpapi_SchemaElementDefinition_getAlternateName(d_impl_p,index);
}

inline std::ostream& SchemaElementDefinition::print(
        std::ostream& stream,
        int level, 
        int spacesPerLevel) const
{
    blpapi_SchemaElementDefinition_print(
            d_impl_p, OstreamWriter,  &stream, level, spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(
        std::ostream& stream, 
        const SchemaElementDefinition& element)
{
    element.print(stream, 0, -1);
    return stream;
}

inline void SchemaElementDefinition::setUserData(void * userData)
{
	blpapi_SchemaElementDefinition_setUserData(d_impl_p, userData);    
}

inline void * SchemaElementDefinition::userData() const
{
	return blpapi_SchemaElementDefinition_userData(d_impl_p);
}

              // --------------------
              // SchemaTypeDefinition
              // --------------------
inline SchemaTypeDefinition::SchemaTypeDefinition(blpapi_SchemaTypeDefinition_t *handle)
: d_impl_p(handle)
{
}

inline SchemaTypeDefinition::~SchemaTypeDefinition()
{
}

inline int SchemaTypeDefinition::datatype() const
{
   return blpapi_SchemaTypeDefinition_datatype(d_impl_p); 
}

inline Name SchemaTypeDefinition::name() const
{
   return blpapi_SchemaTypeDefinition_name(d_impl_p); 
}

inline const char* SchemaTypeDefinition::description() const
{
   return blpapi_SchemaTypeDefinition_description(d_impl_p); 
}

inline int SchemaTypeDefinition::status() const
{
   return blpapi_SchemaTypeDefinition_status(d_impl_p); 
}

inline int SchemaTypeDefinition::numElementDefinitions() const
{
   return BLPAPI_CALL(blpapi_SchemaTypeDefinition_numElementDefinitions)(d_impl_p); 
}

inline bool SchemaTypeDefinition::hasElementDefinition(const Name& name) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinition(
            d_impl_p, 0, name.impl()) ? true : false;
}

inline bool 
SchemaTypeDefinition::hasElementDefinition(const char* nameString) const
{
    return !blpapi_SchemaTypeDefinition_getElementDefinition(
            d_impl_p, nameString, 0) ? true : false;
}

inline SchemaElementDefinition 
SchemaTypeDefinition::getElementDefinition(const Name& name) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinition(d_impl_p, 0, name.impl());
}

inline SchemaElementDefinition 
SchemaTypeDefinition::getElementDefinition(const char* nameString) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinition(d_impl_p, nameString, 0);
}

inline SchemaElementDefinition 
SchemaTypeDefinition::getElementDefinition(size_t index) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinitionAt(d_impl_p, index);
}

inline bool SchemaTypeDefinition::isComplexType() const
{
	return blpapi_SchemaTypeDefinition_isComplexType(d_impl_p);    
}

inline bool SchemaTypeDefinition::isSimpleType() const
{
	return blpapi_SchemaTypeDefinition_isSimpleType(d_impl_p);
}

inline bool SchemaTypeDefinition::isEnumerationType() const
{
	return blpapi_SchemaTypeDefinition_isEnumerationType(d_impl_p);
}

inline std::ostream& SchemaTypeDefinition::print(
        std::ostream& stream,
        int level, 
        int spacesPerLevel) const
{
    blpapi_SchemaTypeDefinition_print(
            d_impl_p, OstreamWriter,  &stream, level, spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(
        std::ostream& stream, 
        const SchemaTypeDefinition& typeDef)
{
    typeDef.print(stream, 0, -1);
    return stream;
}

inline void SchemaTypeDefinition::setUserData(void * userData)
{
	blpapi_SchemaTypeDefinition_setUserData(d_impl_p, userData);
}

inline void * SchemaTypeDefinition::userData() const
{
	return blpapi_SchemaTypeDefinition_userData(d_impl_p);
}

inline const ConstantList SchemaTypeDefinition::enumeration() const
{
	return blpapi_SchemaTypeDefinition_enumeration(d_impl_p);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus

#endif // #ifndef INCLUDED_API_SCHEMA

