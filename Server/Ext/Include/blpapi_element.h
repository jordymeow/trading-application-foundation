#ifndef INCLUDED_BLPAPI_ELEMENT
#define INCLUDED_BLPAPI_ELEMENT

#include <blpapi_types.h>
#include <blpapi_schema.h>
#include <blpapi_datetime.h>
#include <blpapi_name.h>
#include <blpapi_defs.h>
#include <blpapi_streamproxy.h>

#ifdef __cplusplus 
extern "C" {
#endif

struct blpapi_Element;
typedef struct blpapi_Element blpapi_Element_t;

BLPAPI_EXPORT blpapi_Name_t* 
blpapi_Element_name(const blpapi_Element_t *element);
     
BLPAPI_EXPORT const char* 
blpapi_Element_nameString(const blpapi_Element_t *element);

BLPAPI_EXPORT blpapi_SchemaElementDefinition_t* 
blpapi_Element_definition(const blpapi_Element_t* element);

BLPAPI_EXPORT int blpapi_Element_datatype (
        const blpapi_Element_t* element);

BLPAPI_EXPORT int blpapi_Element_isComplexType(
        const blpapi_Element_t* element);

BLPAPI_EXPORT int blpapi_Element_isArray(
        const blpapi_Element_t* element);

BLPAPI_EXPORT int blpapi_Element_isReadOnly(
        const blpapi_Element_t* element);

BLPAPI_EXPORT size_t blpapi_Element_numValues(
        const blpapi_Element_t* element);

BLPAPI_EXPORT size_t blpapi_Element_numElements(
        const blpapi_Element_t* element);

BLPAPI_EXPORT int blpapi_Element_isNullValue(
        const blpapi_Element_t* element, 
        size_t index);

BLPAPI_EXPORT int blpapi_Element_isNull(
        const blpapi_Element_t* element);


BLPAPI_EXPORT int blpapi_Element_print(
        const blpapi_Element_t* element, 
        blpapi_StreamWriter_t streamWriter,
        void *stream,
        int level, 
        int spacesPerLevel);

BLPAPI_EXPORT
int blpapi_Element_getElementAt(
        const blpapi_Element_t* element, 
        blpapi_Element_t **result,
        size_t position);

BLPAPI_EXPORT
int blpapi_Element_getElement(
        const blpapi_Element_t *element, 
        blpapi_Element_t **result,
        const char* nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Element_hasElement(
        const blpapi_Element_t *element, 
        const char* nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Element_hasElementEx(
        const blpapi_Element_t *element, 
        const char* nameString,
        const blpapi_Name_t *name,
        int excludeNullElements,
        int reserved);

BLPAPI_EXPORT
int blpapi_Element_getValueAsBool(
        const blpapi_Element_t *element, 
        blpapi_Bool_t *buffer, 
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsChar(
        const blpapi_Element_t *element, 
        blpapi_Char_t *buffer, 
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_getValueAsUChar(
        const blpapi_Element_t *element,
        blpapi_UChar_t *buffer,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_getValueAsInt32(
        const blpapi_Element_t *element,
        blpapi_Int32_t *buffer,
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_getValueAsUInt32(
        const blpapi_Element_t *element,
        blpapi_UInt32_t *buffer,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_getValueAsInt64(
        const blpapi_Element_t *element,
        blpapi_Int64_t *buffer,
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_getValueAsUInt64(
        const blpapi_Element_t *element,
        blpapi_UInt64_t *buffer,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_getValueAsFloat32(
        const blpapi_Element_t *element,
        blpapi_Float32_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsFloat64(
        const blpapi_Element_t *element,
        blpapi_Float64_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsString(
        const blpapi_Element_t *element,
        const char **buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsDatetime(
        const blpapi_Element_t *element,
        blpapi_Datetime_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsElement(
        const blpapi_Element_t *element,
        blpapi_Element_t **buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsName(
        const blpapi_Element_t *element,
        blpapi_Name_t **buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getChoice(
        const blpapi_Element_t *element,
        blpapi_Element_t **result);

BLPAPI_EXPORT
int blpapi_Element_setValueBool(
        blpapi_Element_t *element, 
        blpapi_Bool_t value, 
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueChar(
        blpapi_Element_t *element, 
        blpapi_Char_t value, 
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_setValueUChar(
        blpapi_Element_t *element,
        blpapi_UChar_t value,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_setValueInt32(
        blpapi_Element_t *element,
        blpapi_Int32_t value,
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_setValueUInt32(
        blpapi_Element_t *element,
        blpapi_UInt32_t value,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_setValueInt64(
        blpapi_Element_t *element,
        blpapi_Int64_t value,
        size_t index);

#if 0
BLPAPI_EXPORT
int blpapi_Element_setValueUInt64(
        blpapi_Element_t *element,
        blpapi_UInt64_t value,
        size_t index);
#endif

BLPAPI_EXPORT
int blpapi_Element_setValueFloat32(
        blpapi_Element_t *element,
        blpapi_Float32_t value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFloat64(
        blpapi_Element_t *element,
        blpapi_Float64_t value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueString(
        blpapi_Element_t *element,
        const char *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueDatetime(
        blpapi_Element_t *element,
        const blpapi_Datetime_t *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFromElement(
        blpapi_Element_t *element,
        blpapi_Element_t *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFromName (
        blpapi_Element_t *element,
        const blpapi_Name_t *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setElementBool(
        blpapi_Element_t *element, 
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Bool_t value); 

BLPAPI_EXPORT
int blpapi_Element_setElementChar(
        blpapi_Element_t *element, 
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Char_t value); 


#if 0
BLPAPI_EXPORT
int blpapi_Element_setElementUChar(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_UChar_t value);
#endif

BLPAPI_EXPORT
int blpapi_Element_setElementInt32(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Int32_t value);

#if 0
BLPAPI_EXPORT
int blpapi_Element_setElementUInt32(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_UInt32_t value);
#endif

BLPAPI_EXPORT
int blpapi_Element_setElementInt64(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Int64_t value);

#if 0
BLPAPI_EXPORT
int blpapi_Element_setElementUInt64(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_UInt64_t value);
#endif

BLPAPI_EXPORT
int blpapi_Element_setElementFloat32(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Float32_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementFloat64(
        blpapi_Element_t *element,
        const char* nameString,
        const blpapi_Name_t* name,
        blpapi_Float64_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementString(
        blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t* name,
        const char *value);
        
BLPAPI_EXPORT
int blpapi_Element_setElementDatetime(
        blpapi_Element_t *element,
        const char* nameString, 
        const blpapi_Name_t* name,
        const blpapi_Datetime_t *value);

BLPAPI_EXPORT
int blpapi_Element_setElementFromField(
        blpapi_Element_t *element,
        const char* nameString, 
        const blpapi_Name_t* name,
        blpapi_Element_t *sourcebuffer);

BLPAPI_EXPORT
int blpapi_Element_setElementFromName (
        blpapi_Element_t *element,
        const char* elementName,
        const blpapi_Name_t* name,
        const blpapi_Name_t *buffer);

BLPAPI_EXPORT
int blpapi_Element_appendElement (
        blpapi_Element_t *element,
        blpapi_Element_t **appendedElement);

BLPAPI_EXPORT
int blpapi_Element_setChoice (
        blpapi_Element_t *element,
        blpapi_Element_t **resultElement,
        const char* nameCstr,
        const blpapi_Name_t* name,
        size_t index);

#ifdef __cplusplus 
}

#include <blpapi_exception.h>
#include <string>

namespace BloombergLP {
namespace blpapi {
	


class Element {
    // Elements are used to represent all input/output values submitted to and
    // received from blpapi services. An Element is a "variant" that can represent
    // any data type supported by blpapi. Elements are used to represent simple
    // scalar values, complex types, and arrays. There are of three families 
    // of accessors/manipulators for getting/setting element values.  The 
    // getValue/setValue familiy of functions are used to operate on simple 
    // scalar values, and arrays.  For simplicity, all 
    // elements are treated as arrays where a scalar is an array limited to 
    // one value.  For instance, to retrieve the first value an array element
    // "a", as a floating pointer number, the following code snippet could be
    // used:
    //..
    //      float f = a.getValueAsFloat32(0);
    //..
    // Similarly, to access the value of a scalar element "s" as a floating
    // point number the following code snippet could be used:
    //..
    //      float f = s.getValueAsFloat32(0);
    //..
    // or
    //..
    //      float f = s.getValueAsFloat32();
    //..
    // To determine the number of values available, the 'numValues' method
    // could be used. For scalar types, it will return a value from 0 to 1.
    // For array's it will return the upper bound of the array.
    //
    // The getElement/setElement familiy of  functions are used to get/set
    // values on complex element types(sequences and choices) . For instance,
    // to set the "city" element of the "address" complex type, the 
    // following code snippet could be used:
    //..
    //      Element address;
    //      ......
    //      address.setElement("city", "New York");
    //..
    // conversly, to retrieve the element "city" from the "address" element, and
    // store it's value in a standard string, the following could be used:
    //..
    //      Element address;
    //      ....
    //      Element city = address.getElement("city");
    //      std::string city_str = city.getValueAsString();
    //..
    // or the following could be used to directly retrieve the value as a
    // string:
    //..
    //      Element address;
    //      ....
    //      std::string city_str = address.getElementAsString("city");
    //..
    // To access the values of an array element, the element must first be
    // retrieved using the 'getElement' method. The values could then be 
    // accessed using the 'getValue' family of accessors.
    // For example, to print out the "emailAddress" array element in the
    // "address" element, the following code snippit could be used:
    //..
    //      Element address;
    //      ...
    //      Element emails = address.getElement("emailAddresses");
    //      for (int i=0,count=emails.numValues(); ++i, i<count) {
    //          std::cout << emails.getValueAsString(i) << std::endl;
    //      }
    //..
    //
    // Elements are recursive.  That is an element 
    ///---------------------------
    ///Data Types
    ///---------------------------
    //
    ///---------------------------
    ///Data conversion
    ///---------------------------
    // All accessors/manipulator


    // Key points
    // Elements have reference semantics.
    // Element life time is linked to it's parent container
    //

    blpapi_Element_t   *d_handle_p;

  public:
	// CREATORS/DESTRUCTORS
    Element();
        // Construct an element object initialized to an invalid state.  See
        // 'rebind()'.

    Element(blpapi_Element_t *element);
        // Construct an element object and associate it with the specified
        // underling blpapi 'element' handle.

    // MANIPULATORS
    void rebind(blpapi_Element_t *element);
        // Re-associate this object with the specified underling blpapi
        // 'element' handle.

    void setElement(const char* name, bool value);
    void setElement(const char* name, char value);
    void setElement(const char* name, Int32 value);
    void setElement(const char* name, Int64 value);
    void setElement(const char* name, Float32 value);
    void setElement(const char* name, Float64 value);
    void setElement(const char* name, long double value);
    void setElement(const char* name, const Datetime& value);
    void setElement(const char* name, const char* value);
    void setElement(const char* name, const Name& value);
    void setElement(const Name& name, bool value);
    void setElement(const Name& name, char value);
    void setElement(const Name& name, Int32 value);
    void setElement(const Name& name, Int64 value);
    void setElement(const Name& name, Float32 value);
    void setElement(const Name& name, Float64 value);
    void setElement(const Name& name, long double value);
    void setElement(const Name& name, const Datetime& value);
    void setElement(const Name& name, const char* value);
    void setElement(const Name& name, const unsigned char* value, int length);
    void setElement(const Name& name, const Name& value);
        // Set the sub-element having the specified 'name' to the specified 
	    // 'value'.  Throw exception if 'name' does not refer to a a valid 
	    // sub-element, or if the specified 'value' is not convertible to a
        // legal value for the sub-element having the specified 'name'.  Note
        // that if the target sub-element already contains multiple values,
        // it will be truncated and replace by the specified single 'value'. Use 
	    // 'getElement(name).setValue(value,index)' where 'index' is the index of 
        // value to be replaced, to set or replace a specific value.
	
    void setValue(bool value, size_t index=0);
    void setValue(char value, size_t index=0);
    void setValue(Int32 value, size_t index=0);
    void setValue(Int64 value, size_t index=0);
    void setValue(Float32 value, size_t index=0);
    void setValue(Float64 value, size_t index=0);
    void setValue(long double value, size_t index=0);
    void setValue(const Datetime& value, size_t index=0);
    void setValue(const char* value, size_t index=0);
    void setValue(const unsigned char* value, 
                  int length, size_t index=0);
        // Set the 'index'th value of this element to the specified 'value'.
        // Throw exception if 'value' is not convertible to a legal value 
        // that can be held by this element, or if 'index' is out of range.

    void setValue(const Name& valueName, size_t index=0);
        // Set the 'index'th value of this element to the value having the
        // specified 'valueName'(e.g., "enumeration constant name").
        // Throw exception if this element does not contain named values, or 
        // if the specified 'valueName' is not a legal value name, or if 
        // 'index' is out of range.

    void appendValue(bool value);
    void appendValue(char value);
    void appendValue(Int32 value);
    void appendValue(Int64 value);
    void appendValue(Float32 value);
    void appendValue(Float64 value);
    void appendValue(long double value);
    void appendValue(const Datetime& value);
    void appendValue(const char* value);
    void appendValue(const unsigned char* value, int length);
	    // Append the specified 'value' to this element. Throw exception if
        // this element is not an array type or  values convertible from the 
        // specified 'value'.  Throw exception otherwise.

    void appendValue(const Name& value);
        // Append to this element a value having the specified 'valueName'
        // (e.g., "enumeration constant name"). Throw exception if this 
        // element does not contain named values, or if the specified 
        // 'valueName' is not a legal value name, or if 'index' is out of 
        // range.


    Element appendElement();
        // Append an element to this element if it represents an array of
        // "complex" types and return the append element.  Throw exception on
        // error.

    Element setChoice(const char* selectionName);
    Element setChoice(const Name& selectionName);
        // Set the selection of this element to the specified 'selectionName' if
        // this element is a "choice" type and contains a slection having the
        // specified 'selectionName'.  If successful, return the selected
        // element, else throw exception.

    blpapi_Element_t* handle();
        // Return the underling blpai element handle associated with this 
        // object. Return 0 if this element is not currently associated with 
        // an underlying blpapi element handle.

	// ACCESSORS
    Name name() const;
	    // Return the primary name associated with this element. Note that
        // alternate names may be available by accessing the schema 
        // definition of this element.  See 'definition()'.

    int datatype() const;
	    // Return the type of value held by this element.  See
        // 'blpapi::Datatype'.

    bool isComplexType() const;
        // Return true if this element is a type that can contain 
        // sub-elements(e.g., "choice", "sequence"), return false otherwise.

    bool isArray() const;
        // Return true if this element is an array type capable of holding
        // multiple values. Return false otherwise.

    bool isNull() const;
        // Return true if this element is in a NULL state. Return false
        // otherwise.

    bool isReadOnly() const;

	SchemaElementDefinition elementDefinition() const;
        // Return a non-modifiable reference to the element definition object
	    // that defines the attributes of this element.

    size_t numValues() const;
	    // Return the number of values contained by this element. For non-array
        // types, return 0 if NULL, or 1 otherwise.  For array types, return
        // the upper bound of the array.
	
    size_t numElements() const;
	   // Return the number of elements contained by this element if it is a complex
	   // element containing sub-elements, return 0 otherwise.

    bool isValid() const;
	   // Retun true if this element object is bound to an underling blpapi element
       // handle. Return false otherwise. Note that the behavior is undefined if 
       // any accessor/manipulator other than 'isValid()', 'rebind()', and
       // 'handle()' are invoked on an element when false == isValid().  Also
       // note that even if 'isValid()' is true, the element may still be 
       // invalid if the underling object is no longer valid.
    
    bool isNullValue(size_t index=0) const;
	  // Return true if the value at the specified 'index' is a "NULL"
	  // value.  Throw exception if index >= numValues().

    bool hasElement(const char* name, bool excludeNullElements = false) const;
    bool hasElement(const Name& name, bool excludeNullElements = false) const;
        // Return true of this element contains a sub-element having the
        // specified 'name'.  Return false otherwise.

    int getValueAs(bool* result, size_t index=0) const;
    int getValueAs(char* result, size_t index=0) const;
    int getValueAs(Int32* result, size_t index=0) const;
	int getValueAs(Int64* result, size_t index=0) const;
    int getValueAs(Float32* result, size_t index=0) const;
    int getValueAs(Float64* result, size_t index=0) const;
    int getValueAs(long double* result, size_t index=0) const;
    int getValueAs(Datetime* result, size_t index=0) const;
    int getValueAs(std::string* result, size_t index=0) const; 
    int getValueAs(Element *result, size_t index=0) const;
    int getValueAs(Name *result, size_t index=0) const;
        // Load into the specified 'result', the value of this element, or if 
	    // specified, the n'th value of this element where n is the optionally
	    // specified 'index'. Return 0 on success and a non-zero error code if
        // 'index' >= 'numValues()', if the value cannot be converted to the
        // specified 'result' type.
    
    bool getValueAsBool        (size_t index=0) const;
        // Return the 'index'th value of the element object as a boolean value. 
        // Throw exception if this element is not convertible to a value boolean,
        // or if 'index' is out of range.

    char getValueAsChar        (size_t index=0) const;
        // Return the 'index'th value of the element object as a character 
        // value. Throw exception if this element is not convertible to character
        // value, or if 'index' is out of range.

    Int32 getValueAsInt32      (size_t index=0) const;
        // Return the 'index'th value of the element object as a 32 bit integer
        // number. Throw exception if this element is not convertible to a
        // 32 bit integer value, or if 'index' is out of range.

    Int64 getValueAsInt64      (size_t index=0) const;
        // Return the 'index'th value of the element object as a 64 bit integer
        // value. Throw exception if this element is not convertible to a
        // 64 bit integer value, or if 'index' is out of range.

    Float32 getValueAsFloat32  (size_t index=0) const;
        // Return the 'index'th value of the element object as a 32 bit float
        // value. Throw exception if this element is not convertible to a
        // boolean, or if 'index' is out of range.

    Float64 getValueAsFloat64  (size_t index=0) const;
        // Return the 'index'th value of the element object as a 64 bit float
        // point value. Throw exception if this element is not convertible to a
        // 64 bit floating point value, or if 'index' is out of range.

    Datetime getValueAsDatetime(size_t index=0) const;
        // Return the 'index'th value of the element object as a date/time value
        // Throw exception if this element is not convertible to a date/time
        // value, or if 'index' is out of range.

    const char* getValueAsString(size_t index=0) const;
        // Return the 'index'th value of the element object as a string value
        // Throw exception if this element is not convertible to a string
        // value, or if 'index' is out of range.

    Element getValueAsElement(size_t index=0) const;

    Name getValueAsName(size_t index=0) const;
        // Return the 'index'th value of this element as a name constant.  
        // Throw exception if this element is not convertible to name 
        // constants or 'index' is out of range.

    int getElement(Element* result, const char *name) const;
    int getElement(Element* result, const Name& name) const;
        // Rebind the specified 'result' element object to the sub-element
        // having the specified 'name'. Return zero on success and a non-zero
        // result if no element having the specified 'name' is available. Note
        // that for modifiable elements, if an element having the specified
        // 'name' does not exists, it will be created if 'name' is a valid
        // member of this element's schema.

    int getElement(Element *result, size_t position) const;

    Element getElement(size_t position) const;
        // Return the 'index'th item of if this element represents an array of
        // complex values. Throw exception if index >= numValues(), or if this
        // element does not represent and array of complext values.

    Element getElement(const Name& name) const;
    Element getElement(const char* name) const;
        // Return the sub-element having the specified 'name'.  Throw exception if
        // there is no sub-element having the specified 'name' is available.

    bool getElementAsBool(const char* name) const;
    bool getElementAsBool(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // boolean value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a boolean value.

    char getElementAsChar(const char* name) const;
    char getElementAsChar(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // character value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a character value.

    Int32 getElementAsInt32(const char* name) const;
    Int32 getElementAsInt32(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // 32 bit integer value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a 32 bit integer value.

    Int64 getElementAsInt64(const char* name) const;
    Int64 getElementAsInt64(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // 64 bit integer value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a 64 bit integer value.

    Float32 getElementAsFloat32(const char* name) const;
    Float32 getElementAsFloat32(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // floating point value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a floating point value.

    Float64 getElementAsFloat64(const char* name) const;
    Float64 getElementAsFloat64(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // floating point value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a floating point value.

    Datetime getElementAsDatetime(const char* name) const;
    Datetime getElementAsDatetime(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // date/time value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a date/time value.

    const char* getElementAsString(const char* name) const;
    const char* getElementAsString(const Name& name) const;
        // Return the value of the sub-element having the specified 'name' as a
        // string value.  Throw exception if no such sub-element is
        // available,no value is availble, or if the specified element is not
        // convertible to a string value.

    Name getElementAsName(const char* name) const;
    Name getElementAsName(const Name& name) const;
        // Return the first value of the sub-element having the specified 
        // 'name' as a 'Name' constant.  Throw exception if no sub-element 
        // having the specified  'name' exists or if a sub-element exists, 
        // but it does not contain a value convertible to a 'Name' constant.

    Element getChoice() const;
        // Return the selection name of this element if this element is a 
        // "choice" element.  Throw exception otherwise.

    const blpapi_Element_t* handle() const;
        // Return the underling blpai element handle associated with this 
        // object. Return 0 if this element is not currently associated with 
        // an underlying blpapi element handle.

    std::ostream& print(std::ostream& stream,
                        int level=0, 
                        int spacesPerLevel=4) const; 
};

// INLINE FUNCTION DEFINITIONS 

inline Element::Element()
: d_handle_p(0)
{
}
    
inline Element::Element(blpapi_Element_t *handle)
: d_handle_p(handle)
{
}

inline void Element::rebind(blpapi_Element_t *element)
{
    d_handle_p = element;
}


inline void Element::setElement(const char* name, bool value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementBool(d_handle_p, name, 0 , value ? 1 :
                0));
}

inline void Element::setElement(const char* name, char value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementChar(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, Int32 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt32(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, Int64 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt64(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, Float32 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setElementFloat32(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, Float64 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setElementFloat64(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, const Datetime& value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementDatetime(d_handle_p, name, 0 , &value.rawValue()));
}

inline void Element::setElement(const char* name, const char* value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementString(d_handle_p, name, 0 , value));
}

inline void Element::setElement(const char* name, const Name& value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementFromName(d_handle_p, name, 0 , value.impl()));
}

inline void Element::setElement(const Name& name, bool value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementBool(d_handle_p, 0, name.impl(), value ? 1 : 0));
}

inline void Element::setElement(const Name& name, char value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementChar(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, Int32 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt32(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, Int64 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt64(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, Float32 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setElementFloat32(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, Float64 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setElementFloat64(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, const Datetime& value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementDatetime(d_handle_p, 0, name.impl(), &value.rawValue()));
}

inline void Element::setElement(const Name& name, const char* value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementString(d_handle_p, 0, name.impl(), value));
}

inline void Element::setElement(const Name& name, const Name& value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementFromName(d_handle_p, 0, name.impl(),
                                              value.impl()));
}

inline void Element::setValue(bool value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueBool(d_handle_p, value, index));
}

inline void Element::setValue(char value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueChar(d_handle_p, value, index));
}

inline void Element::setValue(Int32 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt32(d_handle_p, value, index));
}

inline void Element::setValue(Int64 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt64(d_handle_p, value, index));
}

inline void Element::setValue(Float32 value, size_t index)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFloat32(d_handle_p, value, index));
}

inline void Element::setValue(Float64 value, size_t index)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFloat64(d_handle_p, value, index));
}

inline void Element::setValue(const Datetime& value, size_t index)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueDatetime(d_handle_p, &value.rawValue(), index));
}

inline void Element::setValue(const char* value, size_t index)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueString(d_handle_p, value, index));
}

inline void Element::setValue(const Name& valueName, size_t index)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFromName(d_handle_p, valueName.impl(), index));
}

inline void Element::appendValue(bool value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueBool(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(char value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueChar(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Int32 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt32(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Int64 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt64(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Float32 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFloat32(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Float64 value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFloat64(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const Datetime& value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueDatetime(d_handle_p, &value.rawValue(), BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const char* value)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueString(d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const Name& valueName)
{
    ExceptionUtil::throwOnError(
        blpapi_Element_setValueFromName(d_handle_p, valueName.impl(), 
                                        BLPAPI_ELEMENT_INDEX_END));
}

inline Element Element::appendElement() 
{
    blpapi_Element_t *appendedElement;
    ExceptionUtil::throwOnError(
        blpapi_Element_appendElement(d_handle_p, &appendedElement));
    return Element(appendedElement);
}

inline Element Element::setChoice(const char* selectionName)
{
    blpapi_Element_t *resultElement;
    ExceptionUtil::throwOnError(
        blpapi_Element_setChoice(d_handle_p, &resultElement, selectionName,
            0, 0));
    return Element(resultElement);
}

inline Element Element::setChoice(const Name& selectionName)
{
    blpapi_Element_t *resultElement;
    ExceptionUtil::throwOnError(
        blpapi_Element_setChoice(d_handle_p, &resultElement, 0,
                                 selectionName.impl(), 0));
    return Element(resultElement);
}

inline blpapi_Element_t* Element::handle() 
{
    return d_handle_p;
}

inline Name Element::name() const
{
    return blpapi_Element_name(d_handle_p); 
}

inline int Element::getElement(Element* element, const char *nameString) const
{
    blpapi_Element_t *fldt;
    int rc = blpapi_Element_getElement(d_handle_p, &fldt, nameString, 0);
    if (!rc) element->rebind(fldt);

    return rc;
}

inline int Element::getElement(Element* element, const Name& name) const
{
    blpapi_Element_t *fldt;
    int rc = blpapi_Element_getElement(d_handle_p, &fldt, 0, name.impl());
    if (!rc) element->rebind(fldt);

    return rc;
}

inline int Element::getElement(Element *element, size_t position) const
{
    blpapi_Element_t *fldt;
    int rc = blpapi_Element_getElementAt(d_handle_p, &fldt, position);
    if (!rc) element->rebind(fldt);

    return rc;
}

inline int Element::datatype() const
{
    return blpapi_Element_datatype(d_handle_p);
}

inline bool Element::isComplexType() const
{
    return blpapi_Element_isComplexType(d_handle_p) ? true : false;
}

inline bool Element::isArray() const
{
    return blpapi_Element_isArray(d_handle_p) ? true : false;
}

inline bool Element::isNull() const
{
    return blpapi_Element_isNull(d_handle_p) ? true : false;
}
inline bool Element::isReadOnly() const
{
    return blpapi_Element_isReadOnly(d_handle_p) ? true : false;
}

inline SchemaElementDefinition Element::elementDefinition() const
{
    return blpapi_Element_definition(d_handle_p);
}

inline size_t Element::numValues() const
{
    return blpapi_Element_numValues(d_handle_p);
}

inline size_t Element::numElements() const
{
    return blpapi_Element_numElements(d_handle_p);
}

inline bool Element::isValid() const 
{
    return d_handle_p  ? true : false;
}

inline bool Element::isNullValue(size_t index) const 
{
    return blpapi_Element_isNullValue(d_handle_p, index) != 0;
}

inline bool Element::hasElement(const char* nameString,
                                bool excludeNullElements) const
{
    if (excludeNullElements) {
        return (BLPAPI_CALL(blpapi_Element_hasElementEx)(d_handle_p,
            nameString, 0, excludeNullElements, 0) ? true : false);
    }
    return blpapi_Element_hasElement(d_handle_p, nameString, 0) ? true : false;
}

inline bool Element::hasElement(const Name& name,
                                bool excludeNullElements) const
{
    if (excludeNullElements) {
        return (BLPAPI_CALL(blpapi_Element_hasElementEx)(d_handle_p, 0,
            name.impl(), excludeNullElements, 0) ? true : false);
    }
    return blpapi_Element_hasElement(d_handle_p, 0, name.impl()) ? true : false;
}

inline Element Element::getElement(const Name& name) const
{
    blpapi_Element_t *fldt;
    ExceptionUtil::throwOnError(
                blpapi_Element_getElement(
                    d_handle_p, 
                    &fldt,
                    0,
                    name.impl()));
    return Element(fldt);
}

inline Element Element::getElement(const char* name) const
{
    blpapi_Element_t *fldt;
    ExceptionUtil::throwOnError(
            blpapi_Element_getElement(
                d_handle_p, 
                &fldt, 
                name,
                0));
    return Element(fldt);
}

inline Element Element::getElement(size_t position) const
{
    blpapi_Element_t *element;
    blpapi_Element_getElementAt(d_handle_p, &element, position);
    return element;
}

inline int Element::getValueAs(bool* buffer, size_t index) const
{
    blpapi_Bool_t tmp=false;

    int res = blpapi_Element_getValueAsBool(d_handle_p, &tmp, index);
    *buffer = tmp ? true : false;
    return res;
}

inline int Element::getValueAs(char* buffer, size_t index) const
{
    return blpapi_Element_getValueAsChar(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Int32* buffer, size_t index) const
{
    return blpapi_Element_getValueAsInt32(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Int64* buffer, size_t index) const
{
    return blpapi_Element_getValueAsInt64(d_handle_p,buffer, index);
}

inline int Element::getValueAs(Float32* buffer, size_t index) const
{
    return blpapi_Element_getValueAsFloat32(d_handle_p,buffer, index);
}

inline int Element::getValueAs(Float64* buffer, size_t index) const
{
    return blpapi_Element_getValueAsFloat64(d_handle_p,buffer, index);
}

inline int Element::getValueAs(Datetime* buffer, size_t index) const
{
    return blpapi_Element_getValueAsDatetime(
            d_handle_p, 
            &buffer->rawValue(), 
            index);
}

inline int Element::getValueAs(std::string* result, size_t index) const
{
    const char* buffer;
    int rc = blpapi_Element_getValueAsString(d_handle_p,&buffer, index);
    if (!rc) *result = buffer;
    return rc;
}
 
inline int Element::getValueAs(Element *buffer, size_t index) const
{
    return blpapi_Element_getValueAsElement(
            d_handle_p, 
            &buffer->d_handle_p, 
            index);
}

inline int Element::getValueAs(Name *buffer, size_t index) const
{
    blpapi_Name_t* tmpName;
    int res = blpapi_Element_getValueAsName(d_handle_p, 
                                            &tmpName,
                                            index);
    if (!res) *buffer = Name(tmpName); 
    return res;
}

inline bool Element::getValueAsBool(size_t index) const
{
    bool value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline char Element::getValueAsChar(size_t index) const
{
    char value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int32 Element::getValueAsInt32(size_t index) const
{
    Int32 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int64 Element::getValueAsInt64(size_t index) const
{
    Int64 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Float32 Element::getValueAsFloat32(size_t index) const
{
    Float32 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Float64 Element::getValueAsFloat64(size_t index) const
{
    Float64 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Datetime Element::getValueAsDatetime(size_t index) const
{
    Datetime value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline const char* Element::getValueAsString(size_t index) const
{
    const char* tmpStringBuffer;
    ExceptionUtil::throwOnError(blpapi_Element_getValueAsString(
                                d_handle_p,
                                &tmpStringBuffer,
                                index));
    return tmpStringBuffer;
}

inline Element Element::getValueAsElement(size_t index) const
{
    blpapi_Element_t *element;
    ExceptionUtil::throwOnError(blpapi_Element_getValueAsElement(d_handle_p, &element, index));
    return Element(element);
}

inline Name Element::getValueAsName(size_t index) const
{
    blpapi_Name_t *name;
    ExceptionUtil::throwOnError(blpapi_Element_getValueAsName(d_handle_p, &name, index));
    return name;
}

inline bool Element::getElementAsBool(const char* name) const
{
    return getElement(name).getValueAsBool();
}

inline bool Element::getElementAsBool(const Name& name) const
{
    return getElement(name).getValueAsBool();
}

inline char Element::getElementAsChar(const char* name) const
{
    return getElement(name).getValueAsChar();
}

inline char Element::getElementAsChar(const Name& name) const
{
    return getElement(name).getValueAsChar();
}

inline Int32 Element::getElementAsInt32(const char* name) const
{
    return getElement(name).getValueAsInt32();
}

inline Int32 Element::getElementAsInt32(const Name& name) const
{
    return getElement(name).getValueAsInt32();
}

inline Int64 Element::getElementAsInt64(const char* name) const
{
    return getElement(name).getValueAsInt64();
}

inline Int64 Element::getElementAsInt64(const Name& name) const
{
    return getElement(name).getValueAsInt64();
}

inline Float32 Element::getElementAsFloat32(const char* name) const
{
    return getElement(name).getValueAsFloat32();
}

inline Float32 Element::getElementAsFloat32(const Name& name) const
{
    return getElement(name).getValueAsFloat32();
}

inline Float64 Element::getElementAsFloat64(const char* name) const
{
    return getElement(name).getValueAsFloat64();
}

inline Float64 Element::getElementAsFloat64(const Name& name) const
{
    return getElement(name).getValueAsFloat64();
}

inline Datetime Element::getElementAsDatetime(const char* name) const
{
    return getElement(name).getValueAsDatetime();
}

inline Datetime Element::getElementAsDatetime(const Name& name) const
{
    return getElement(name).getValueAsDatetime();
}

inline const char* Element::getElementAsString(const char* name) const
{
    return getElement(name).getValueAsString();
}

inline const char* Element::getElementAsString(const Name& name) const
{
    return getElement(name).getValueAsString();
}

inline Name Element::getElementAsName(const char* name) const
{
    return getElement(name).getValueAsName();
}

inline Name Element::getElementAsName(const Name& name) const
{
    return getElement(name).getValueAsName();
}

inline const blpapi_Element_t* Element::handle() const
{
    return d_handle_p;
}

inline std::ostream& Element::print(
        std::ostream& stream,
        int level, 
        int spacesPerLevel) const
{
    blpapi_Element_print(
            d_handle_p, OstreamWriter,  &stream, level, spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Element& element)
{
    element.print(stream, 0, -1);
    return stream;
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_ELEMENT


