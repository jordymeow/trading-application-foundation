// blpapi_constant.h     -*-C++-*-

#ifndef INCLUDED_BLPAPI_CONSTANT_H
#define INCLUDED_BLPAPI_CONSTANT_H

#include <blpapi_types.h>
#include <blpapi_name.h>
#include <blpapi_defs.h>
#include <blpapi_datetime.h>
#include <blpapi_exception.h>
#include <blpapi_call.h>

#ifdef __cplusplus 
extern "C" {
#endif

struct blpapi_Constant;
typedef struct blpapi_Constant blpapi_Constant_t;

struct blpapi_ConstantList;
typedef struct blpapi_ConstantList blpapi_ConstantList_t;


BLPAPI_EXPORT
void blpapi_Constant_setUserData(
		blpapi_Constant_t *constant,
		void * userdata);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_Constant_name(
        const blpapi_Constant_t *constant);

BLPAPI_EXPORT
const char* blpapi_Constant_description(
        const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_status(
        const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_datatype(
        const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsChar(
		const blpapi_Constant_t *constant,
		blpapi_Char_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsInt32(
		const blpapi_Constant_t *constant,
		blpapi_Int32_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsInt64(
		const blpapi_Constant_t *constant,
		blpapi_Int64_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsFloat32(
		const blpapi_Constant_t *constant,
		blpapi_Float32_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsFloat64(
		const blpapi_Constant_t *constant,
		blpapi_Float64_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsDatetime(
		const blpapi_Constant_t *constant,
		blpapi_Datetime_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsString(
		const blpapi_Constant_t *constant,
		const char **buffer);

BLPAPI_EXPORT
void * blpapi_Constant_userData(
		const blpapi_Constant_t *constant);


BLPAPI_EXPORT
void blpapi_ConstantList_setUserData(
		blpapi_ConstantList_t *constant,
		void * userdata);

BLPAPI_EXPORT
blpapi_Name_t* blpapi_ConstantList_name(
        const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
const char* blpapi_ConstantList_description(
        const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
int blpapi_ConstantList_numConstants(
        const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
int blpapi_ConstantList_datatype(
        const blpapi_ConstantList_t *constant);

BLPAPI_EXPORT
int blpapi_ConstantList_status(
        const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
blpapi_Constant_t* blpapi_ConstantList_getConstant(
        const blpapi_ConstantList_t *constant,
        const char *nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Constant_t* blpapi_ConstantList_getConstantAt(
        const blpapi_ConstantList_t *constant,
        size_t index);

BLPAPI_EXPORT
void * blpapi_ConstantList_userData(
		const blpapi_ConstantList_t *constant);

#ifdef __cplusplus 
}


namespace BloombergLP {
namespace blpapi {

class Constant {
    blpapi_Constant_t *d_impl_p;
  public:
	// CREATORS
    Constant(blpapi_Constant_t *handle);

	Constant(const Constant& original);    

	// MANIPULATORS
	void setUserData(void * userData);

    // ACCESSORS
    Name name() const;
    // Return the symbolic name of this constant value.

    const char* description() const;
    // Return a pointer to the description of this constant value.

    int status() const;
    // Return the status of this constant value.

    int datatype() const;
    // Return the data type used to represent the value of this constant.

    const blpapi_Constant_t* impl() const;

	int getValueAs(char* buffer) const;
    int getValueAs(Int32* buffer) const;
    int getValueAs(Int64* buffer) const;
    int getValueAs(Float32* buffer) const;    
    int getValueAs(Float64* buffer) const;
	int getValueAs(Datetime* buffer) const;
	int getValueAs(std::string* buffer) const;    

	char getValueAsChar() const;
    Int32 getValueAsInt32() const;
    Int64 getValueAsInt64() const;
    Float32 getValueAsFloat32() const;    
    Float64 getValueAsFloat64() const;
	Datetime getValueAsDatetime() const;
	std::string getValueAsString() const;    

	void * userData() const;
};

class ConstantList {
    blpapi_ConstantList_t *d_impl_p;
  public:
    ConstantList(blpapi_ConstantList_t *handle);

	ConstantList(const ConstantList& original);

	// MANIPULATORS
	void setUserData(void * userData);

    // ACCESSORS
    Name name() const;
    // Return the symbolic name of this list of constants.

    char const* description() const;
    // Return the description of this list of constansts.

    int numConstants() const;
    // Return the number of constants contained in this constant list.

    int status() const;
    // Return the status of this list of constants.

    int datatype() const;
    // Return the datatype of constants contained in this list of 
    // constants.

    Constant getConstant(const Name& name) const;
    // Return the constant having the specified 'name'.  Throw exception
    // if this constant list does containing having the specified 'name'.

    Constant getConstant(const char* nameString) const;

    Constant getConstantAt(size_t index) const;
    // Return the constant at the specified 'index' in this list of 
    // constants.  Throw exception if this 'index' < 0 or if 
    // index >= 'numConstants()'.

    const blpapi_ConstantList_t* impl() const;

	void * userData() const;
};

inline Constant::Constant(blpapi_Constant_t *handle)
: d_impl_p(handle)
{
}

inline Constant::Constant(
			const Constant& original)
: d_impl_p(original.d_impl_p)
{
}

inline Name Constant::name() const
{
    return blpapi_Constant_name(d_impl_p);
}

inline const char* Constant::description() const
{
    return blpapi_Constant_description(d_impl_p);
}

inline int Constant::status() const
{
    return blpapi_Constant_status(d_impl_p);
}

inline int Constant::datatype() const
{
    return blpapi_Constant_datatype(d_impl_p);
}

inline const blpapi_Constant_t* Constant::impl() const
{
    return d_impl_p;
}

inline int Constant::getValueAs(char* buffer) const
{
	return blpapi_Constant_getValueAsChar(d_impl_p, buffer);    
}

inline int Constant::getValueAs(Int32* buffer) const
{
	return blpapi_Constant_getValueAsInt32(d_impl_p, buffer);    
}

inline int Constant::getValueAs(Int64* buffer) const
{
	return blpapi_Constant_getValueAsInt64(d_impl_p, buffer);
}

inline int Constant::getValueAs(Float32* buffer) const
{
	return blpapi_Constant_getValueAsFloat32(d_impl_p, buffer);
}

inline int Constant::getValueAs(Float64* buffer) const
{
	return blpapi_Constant_getValueAsFloat64(d_impl_p, buffer);
}

inline int Constant::getValueAs(Datetime* buffer) const
{
	return blpapi_Constant_getValueAsDatetime(d_impl_p, &buffer->rawValue());
}

inline int Constant::getValueAs(std::string* result) const
{	
	const char* buffer;
	int rc = blpapi_Constant_getValueAsString(d_impl_p, &buffer);
	if (!rc) *result = buffer;
	return rc; 
}


inline char Constant::getValueAsChar() const
{
	char value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int32 Constant::getValueAsInt32() const
{
	int value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int64 Constant::getValueAsInt64() const
{
	Int64 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline float Constant::getValueAsFloat32() const
{
	Float32 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline double Constant::getValueAsFloat64() const
{
	Float64 value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Datetime Constant::getValueAsDatetime() const
{
	Datetime value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline std::string Constant::getValueAsString() const
{
	std::string value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline void Constant::setUserData(void * userData)
{
	blpapi_Constant_setUserData(d_impl_p, userData);
}

inline void * Constant::userData() const
{
	return blpapi_Constant_userData(d_impl_p);
}



inline ConstantList::ConstantList(
        blpapi_ConstantList_t *handle)
: d_impl_p(handle)
{
}

inline ConstantList::ConstantList(
		const ConstantList& original)
: d_impl_p(original.d_impl_p)
{
}

inline Name ConstantList::name() const
{
    return blpapi_ConstantList_name(d_impl_p);
}

inline const char* ConstantList::description() const
{
    return blpapi_ConstantList_description(d_impl_p);
}

inline int ConstantList::status() const
{
    return blpapi_ConstantList_status(d_impl_p);
}

inline int ConstantList::datatype() const
{
    return blpapi_ConstantList_datatype(d_impl_p);
}

inline int ConstantList::numConstants() const
{
    return blpapi_ConstantList_numConstants(d_impl_p);
}

inline Constant ConstantList::getConstant(const Name& name) const
{
    return blpapi_ConstantList_getConstant(d_impl_p, 0, name.impl());
}

inline Constant ConstantList::getConstant(const char* nameString) const
{
    return blpapi_ConstantList_getConstant(d_impl_p, nameString, 0 );
}

inline Constant ConstantList::getConstantAt(size_t index) const
{
    return blpapi_ConstantList_getConstantAt(d_impl_p, index);
}

inline const blpapi_ConstantList_t* ConstantList::impl() const
{
    return d_impl_p;
}

inline void ConstantList::setUserData(void * userData)
{
	blpapi_ConstantList_setUserData(d_impl_p, userData);
}

inline void * ConstantList::userData() const
{
	return blpapi_ConstantList_userData(d_impl_p);
}


} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifndef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_Constant_H

