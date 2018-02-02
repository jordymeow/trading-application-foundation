// blpapi_subscriptionlist.h     -*-C++-*-

#ifndef INCLUDED_BLPAPI_SUBSCRIPTIONLIST
#define INCLUDED_BLPAPI_SUBSCRIPTIONLIST

#include <blpapi_types.h>
#include <blpapi_correlationid.h>
#include <blpapi_defs.h>

struct blpapi_SubscriptionList;
typedef struct blpapi_SubscriptionList blpapi_SubscriptionList_t;

#ifdef __cplusplus 
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_SubscriptionList_t* blpapi_SubscriptionList_create();

BLPAPI_EXPORT
void blpapi_SubscriptionList_destroy(
        blpapi_SubscriptionList_t *list);

BLPAPI_EXPORT
int blpapi_SubscriptionList_add(
        blpapi_SubscriptionList_t* list,
        const char* topic,
        const blpapi_CorrelationId_t *correlationId,
        const char** fields,
        const char** options,
        int numfields,
        int numOptions);

BLPAPI_EXPORT
int blpapi_SubscriptionList_clear(
        blpapi_SubscriptionList_t* list);

BLPAPI_EXPORT
int blpapi_SubscriptionList_append(
        blpapi_SubscriptionList_t* dest,
        const blpapi_SubscriptionList_t* src);

BLPAPI_EXPORT
int blpapi_SubscriptionList_size(
        const blpapi_SubscriptionList_t *list);

BLPAPI_EXPORT
int blpapi_SubscriptionList_correlationIdAt(
        const blpapi_SubscriptionList_t* list,
        blpapi_CorrelationId_t* result, 
        size_t index);

BLPAPI_EXPORT
int blpapi_SubscriptionList_topicStringAt(
        blpapi_SubscriptionList_t* list, 
        const char** result, 
        size_t index);


#ifdef __cplusplus 
}

#include <blpapi_exception.h>
#include <cstring>
#include <vector>
#include <string>

namespace BloombergLP {
namespace blpapi {

class SubscriptionListImpl;

                         // ======================
                         // class SubscriptionList
                         // ======================

class SubscriptionList { 
    blpapi_SubscriptionList_t *d_handle_p; // Underlining "C" subscription
                                           // list handle

  public:
    // CREATORS
	SubscriptionList();
        // Construct an empty subscription list.

	SubscriptionList(const SubscriptionList& original);
        // Construct a subscription list having the values of the specified
        // 'original' subscription list.

	~SubscriptionList();
        // Destroy this subscription list.

    // MANIPULATORS
	int add(char const* topic);
	int add(char const* topic, 
            const CorrelationId& correlationID);
        // Add to this subscription list the specified 'topic' and associate 
        // and optionally specified 'correlationID'.

	int add(char const* topic, 
            const char* fields,
            const char* options,
            const CorrelationId& correlationId);
        // Add to this subscription list. TODO

	int add(char const* topic, 
            const std::vector<std::string>& fields,
            const std::vector<std::string>& options,
            const CorrelationId& correlationId);
        // TODO

	int add(const CorrelationId& correlationID);
        // Add to this subscription list, the specified 'correlationID' with no
        // associated topic string.  Return 0 on sucess and a non-zero value
        // otherwise.

    int append(const SubscriptionList& rhs);
        // Append to this subscription list, the contents of the specified 'rhs'
        // subscription list.

    void clear();
        // Remove all items from this subscription list.

	SubscriptionList& operator=(const SubscriptionList& rhs);
        // Replace the contents of this subscription list with contents of the 
        // specified 'rhs' subscription list and return a modifiable reference
        // to this subscription list.

    // ACCESSORS
    size_t size() const;
        // Return the number of items contained by this subscription list.

	CorrelationId correlationIdAt(size_t index) const;
        // Return the correlation id associated the 'index'th item in this 
        // subscription list(zero relative).  Throw and IndexOutOfBounds 
        // exception if 'index' >= 'size()'.

	char const* topicStringAt(size_t index) const;
        // Return a non-modifiable pointer to the the topic string at the
        // 'index'th position in this subscription list(zero relative).
        // Throw and IndexOutOfBounds exception if 'index' >= 'size()'.
        // Note that the returned pointer is only valid while this subscripion
        // list is valid and NOT modified.
    
    const blpapi_SubscriptionList_t* impl() const;
        // Return a pointer to the underlying "C" subscription list handle.
};

// ===========================================================================
//                        INLINE FUNCTION DEFINITIONS
// ===========================================================================

// CREATORS
inline SubscriptionList::SubscriptionList()
: d_handle_p(blpapi_SubscriptionList_create())
{
    if (!d_handle_p) {
        // TODO
    }
}

inline SubscriptionList::SubscriptionList(
        const SubscriptionList& original)
: d_handle_p(blpapi_SubscriptionList_create())
{
    if (!d_handle_p) {

    }
    blpapi_SubscriptionList_append(d_handle_p, original.d_handle_p);
}


inline SubscriptionList::~SubscriptionList()
{
    blpapi_SubscriptionList_destroy(d_handle_p);    
}

// MANIPULATORS
inline int SubscriptionList::add(char const* topic)
{
    blpapi_CorrelationId_t correlationId;
    std::memset(&correlationId, 0, sizeof(correlationId));
    return blpapi_SubscriptionList_add(d_handle_p, 
                                       topic,
                                       &correlationId,
                                       0,0,0,0);
}

inline int SubscriptionList::add(char const* topic, 
                                 const CorrelationId& correlationId)
{
    return blpapi_SubscriptionList_add(d_handle_p, 
                                       topic, 
                                       &correlationId.impl(),
                                       0,0,0,0
                                       );
}

inline int SubscriptionList::add(
        char const* topic, 
        const char* fields,
        const char* options,
        const CorrelationId& correlationId)
{
    return blpapi_SubscriptionList_add(d_handle_p,
                                       topic,
                                       &correlationId.impl(),
                                       &fields,
                                       &options,
                                       fields ? 1 : 0,
                                       options ? 1 : 0 );

}

inline int SubscriptionList::add(
        char const* topic, 
        const std::vector<std::string>& fields,
        const std::vector<std::string>& options,
        const CorrelationId& correlationId)
{
    std::vector<const char*> tmpVector;
    const char* arena[256];
    const char** tmpArray=arena;
    int sizeNeeded = fields.size() + options.size();

    if (sizeNeeded > sizeof(arena)/sizeof(arena[0])) {
        tmpVector.resize(sizeNeeded);
        tmpArray = &tmpVector[0];
    }

    const char** p = tmpArray;
    for (std::vector<std::string>::const_iterator itr = fields.begin(),
            end = fields.end(); itr != end; ++itr, ++p) {
        *p = itr->c_str();
    }

    for (std::vector<std::string>::const_iterator itr = options.begin(),
            end = options.end(); itr != end; ++itr, ++p) {
        *p = itr->c_str();
    }
    
    return blpapi_SubscriptionList_add(d_handle_p,
                                       topic,
                                       &correlationId.impl(),
                                       tmpArray,
                                       tmpArray + fields.size(),
                                       fields.size(),
                                       options.size());


}

inline int SubscriptionList::add(const CorrelationId& correlationId)
{
    return blpapi_SubscriptionList_add(d_handle_p, 
                                       "", 
                                       &correlationId.impl(),
                                       0, 0, 0, 0);
}

inline int SubscriptionList::append(const SubscriptionList& rhs)
{
    return blpapi_SubscriptionList_append(d_handle_p, rhs.d_handle_p);
}

inline void SubscriptionList::clear()
{
    blpapi_SubscriptionList_clear(d_handle_p);
}

inline SubscriptionList& SubscriptionList::operator=(
        const SubscriptionList& rhs)
{
    blpapi_SubscriptionList_clear(d_handle_p);
    blpapi_SubscriptionList_append(d_handle_p, rhs.d_handle_p);
    return *this;
}

// ACCESSORS
inline size_t SubscriptionList::size() const
{
    return blpapi_SubscriptionList_size(d_handle_p);
}

inline CorrelationId SubscriptionList::correlationIdAt(size_t index) const
{
    blpapi_CorrelationId_t correlationId;

    ExceptionUtil::throwOnError(
            blpapi_SubscriptionList_correlationIdAt(d_handle_p, &correlationId,
            index));

    return CorrelationId(correlationId);
}

inline char const* SubscriptionList::topicStringAt(size_t index) const
{
    const char* result;

    ExceptionUtil::throwOnError(
            blpapi_SubscriptionList_topicStringAt(
                d_handle_p,
                &result, 
                index));

    return result;
}

inline const blpapi_SubscriptionList_t* SubscriptionList::impl() const
{
    return d_handle_p;
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif /* ifdef __cplusplus  */


#endif // #ifndef INCLUDED_BLPAPI_SUBSCRIPTIONLIST

