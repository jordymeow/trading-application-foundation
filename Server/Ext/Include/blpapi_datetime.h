// blpapi_datetime.h     -*-C++-*-

#ifndef INCLUDED_API_DATETIME
#define INCLUDED_API_DATETIME

#include <blpapi_types.h>
#include <blpapi_defs.h>

struct blpapi_Datetime_tag {
    blpapi_UChar_t  parts;        /* bitmask of date/time parts that are set */
    blpapi_UChar_t  hours;
    blpapi_UChar_t  minutes;
    blpapi_UChar_t  seconds;
    blpapi_UInt16_t milliSeconds;
    blpapi_UChar_t  month;
    blpapi_UChar_t  day;
    blpapi_UInt16_t year;
    blpapi_Int16_t  offset;
};

typedef struct blpapi_Datetime_tag blpapi_Datetime_t;

#ifdef __cplusplus

#include <cstring> // for std::memset

namespace BloombergLP {
namespace blpapi {

struct DatetimeParts {
    enum Value {
          YEAR         = BLPAPI_DATETIME_YEAR_PART
        , MONTH        = BLPAPI_DATETIME_MONTH_PART
        , DAY          = BLPAPI_DATETIME_DAY_PART
        , OFFSET       = BLPAPI_DATETIME_OFFSET_PART
        , HOURS        = BLPAPI_DATETIME_HOURS_PART
        , MINUTES      = BLPAPI_DATETIME_MINUTES_PART
        , SECONDS      = BLPAPI_DATETIME_SECONDS_PART
        , MILLISECONDS = BLPAPI_DATETIME_MILLISECONDS_PART
        , DATE         = BLPAPI_DATETIME_DATE_PART
        , TIME         = BLPAPI_DATETIME_TIME_PART
        , TIMEMILLI    = BLPAPI_DATETIME_TIMEMILLI_PART
    };
};

class Datetime {
    blpapi_Datetime_t d_value;

    static bool isLeapYear(int year);

    static bool isValidDate(int year, int month, int day);

    static bool isValidTime(int hours, int minutes, int seconds, int milliSeconds);

  public:
    // CREATORS
    // TODO: add more constructors 

    Datetime(const Datetime& original);
        // Construct a 'Datetime' object having the value of the specifed
        // 'original' object.

    Datetime();
        // Construct a 'Datetime' object initialized to an unset state.

    Datetime(const blpapi_Datetime_t rawValue);
        // Construct a 'Datetime' object having the specified 'rawValue'.


    // MANIPULATORS
    Datetime& operator=(const Datetime& rhs);
        // Assign to this 'Datetime' object the value of the specified 'rhs'
        // object.

    void setDate(unsigned year, 
                 unsigned month, 
                 unsigned day);
        // Set the date of the 'Datetime' object to the specified 'day',
        // 'month', and 'year' respectively.

    void setTime(unsigned hours, 
                 unsigned minutes, 
                 unsigned seconds);
        // Set the time of the 'Datetime' object to the specified 'hours',
        // 'minutes', and 'seconds' respectively.  Note that the millisecond
        // value of this date time will be cleared.

    void setTime(unsigned hours, 
                 unsigned minutes, 
                 unsigned seconds, 
                 unsigned milliSeconds);
        // Set the time of the 'Datetime' object to the specified 'hours',
        // 'minutes', and 'seconds' respectively. 

    void setOffset(short value);
        // Set the offset value of this 'Datetime' object to the specifed
        // 'value'.

    void setMonth(unsigned value);
        // Set the month value of this 'Datetime' object to the specifed
        // 'value'.

    void setDay(unsigned value);
        // Set the day value of this 'Datetime' object to the specifed
        // 'value'.

    void setYear(unsigned value);
        // Set the year value of this 'Datetime' object to the specifed
        // 'value'.

    void setHours(unsigned value);
        // Set the hours value of this 'Datetime' object to the specifed
        // 'value'.

    void setMinutes(unsigned value);
        // Set the minutes value of this 'Datetime' object to the specifed
        // 'value'.

    void setSeconds(unsigned value);
        // Set the seconds value of this 'Datetime' object to the specifed
        // 'value'.

    void setMilliseconds(unsigned value);
        // Set the milliseconds value of this 'Datetime' object to the specifed
        // 'value'.

    blpapi_Datetime_t& rawValue();

    // ACCESSORS
    short offset() const;
        // Return the offset value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a offset value set.

    unsigned month() const;
        // Return the month value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a month value set.

    unsigned day() const;
        // Return the day value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a day value set.

    unsigned year() const;
        // Return the year value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a year value set.

    unsigned hours() const;
        // Return the hours value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a hours value set.

    unsigned minutes() const;
        // Return the minutes value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a minutes value set.

    unsigned seconds() const;
        // Return the seconds value of this 'Datetime' object.  Note that the
        // result is undefined unless object has a seconds value set.


    unsigned milliSeconds() const;
        // Return the milliseconds value of this 'Datetime' object.  Note that
        // the result is undefined unless object has a milliseconds value set.

    const blpapi_Datetime_t& rawValue() const;
        // Return the value of this 'Datetime' object as a 'blpapi_Datetime_t'
        // value;

    bool hasParts(unsigned  parts) const;
        // Return true of this 'Datetime' object has all of the specified parts
        // set. 

    unsigned parts() const;
        // Return a bitmask of all parts that are set in this 'Datetime' 
        // object.  Set 'DatetimeParts' for a list of bit enumerators.

    bool isValid() const;
        // Check whether the value of this 'Datetime' is valid.
};

inline bool operator==(const Datetime& lhs, const Datetime& rhs)
{
    return (std::memcmp(&lhs.rawValue(), &rhs.rawValue(),
        sizeof(blpapi_Datetime_t)) == 0);
}

inline Datetime::Datetime(const Datetime& original)
: d_value(original.d_value)
{
}

inline Datetime::Datetime()
{
    std::memset(&d_value, 0, sizeof(d_value));
    d_value.year = 1;
    d_value.month = 1;
    d_value.day = 1;    
}

inline Datetime::Datetime(const blpapi_Datetime_t rawValue)
: d_value(rawValue)
{
}

// MANIPULATORS
inline Datetime& Datetime::operator=(const Datetime& rhs)
{
    if (&rhs != this) d_value = rhs.d_value;
    return *this;
}

inline void Datetime::setDate(unsigned year, 
                              unsigned month, 
                              unsigned day)
{    
    d_value.day   = day;
    d_value.month = month;
    d_value.year  = year;
    d_value.parts |= DatetimeParts::DATE;
}


inline void Datetime::setTime(unsigned hours, 
                              unsigned minutes, 
                              unsigned seconds)
{    
    d_value.hours        = hours;
    d_value.minutes      = minutes;
    d_value.seconds      = seconds;
    d_value.milliSeconds = 0;
    d_value.parts        = (d_value.parts & ~DatetimeParts::TIMEMILLI) | 
                           DatetimeParts::TIME;
}


inline void Datetime::setTime(unsigned hours, 
                              unsigned minutes, 
                              unsigned seconds, 
                              unsigned milliSeconds)
{    
    d_value.hours        = hours;
    d_value.minutes      = minutes;
    d_value.seconds      = seconds;
    d_value.milliSeconds = milliSeconds;
    d_value.parts       |= DatetimeParts::TIMEMILLI;
}


inline void Datetime::setOffset(short value)
{
    d_value.offset = value;
    d_value.parts |= DatetimeParts::OFFSET;
}


inline void Datetime::setMonth(unsigned value)
{    
    d_value.month  = value;
    d_value.parts |= DatetimeParts::MONTH;
}


inline void Datetime::setDay(unsigned value)
{
    d_value.day    = value;
    d_value.parts |= DatetimeParts::DAY;
}

inline void Datetime::setYear(unsigned value)
{
    d_value.year   = value;
    d_value.parts |= DatetimeParts::YEAR;
}


inline void Datetime::setHours(unsigned value)
{
    d_value.hours  = value;
    d_value.parts |= DatetimeParts::HOURS;
}


inline void Datetime::setMinutes(unsigned value)
{
    d_value.minutes  = value;
    d_value.parts   |= DatetimeParts::MINUTES;
}


inline void Datetime::setSeconds(unsigned value)
{
    d_value.seconds  = value;
    d_value.parts   |= DatetimeParts::SECONDS;
}


inline void Datetime::setMilliseconds(unsigned value)
{
    d_value.milliSeconds = value;
    d_value.parts       |= DatetimeParts::MILLISECONDS;
}

inline blpapi_Datetime_t& Datetime::rawValue()
{
    return d_value;
}

// ACCESSORS
inline short Datetime::offset() const
{
    return d_value.offset;
}

inline unsigned Datetime::month() const
{
    return d_value.month;
}

inline unsigned Datetime::day() const
{
    return d_value.day;
}

inline unsigned Datetime::year() const
{
    return d_value.year;
}

inline unsigned Datetime::hours() const
{
    return d_value.hours;
}

inline unsigned Datetime::minutes() const
{
    return d_value.minutes;
}

inline unsigned Datetime::seconds() const
{
    return d_value.seconds;
}

inline unsigned Datetime::milliSeconds() const
{
    return d_value.milliSeconds;
}

inline const blpapi_Datetime_t& Datetime::rawValue() const
{
    return d_value;
}

inline unsigned Datetime::parts() const
{
    return d_value.parts;
}

inline bool Datetime::hasParts(unsigned  parts) const
{   
    return parts == (d_value.parts & parts);
}

inline bool Datetime::isValid() const
{    
    if ( (hasParts(DatetimeParts::YEAR) || hasParts(DatetimeParts::MONTH) ||
            hasParts(DatetimeParts::DAY) )
         && !isValidDate(year(), month(), day()) )
         return false;
    if ( (hasParts(DatetimeParts::HOURS) || hasParts(DatetimeParts::MINUTES) ||
        hasParts(DatetimeParts::SECONDS) || hasParts(DatetimeParts::MILLISECONDS))
        && !isValidTime(hours(), minutes(), seconds(), milliSeconds()) )
        return false;
    return true;
}

inline bool Datetime::isLeapYear(int y)
{
    return 0 == y % 4 && (y <= 1752 || 0 != y % 100 || 0 == y % 400);
}

inline bool Datetime::isValidDate(int year, 
                                  int month, 
                                  int day)
{
    if ((year <= 0) || (year > 9999) ||
        (month <= 0) || (month > 12) 
        || (day <= 0) || (day > 31) )        		
        return false;
    if (day < 29) return true;
    if (year == 1752) 
        if (month == 9 && day > 2 && day < 14) return false;        
    switch (month) {
        case 1: 
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return true;
        case 4:        	
        case 6:
        case 9:        		
        case 11:
            if (day > 30) return false;
            else return true;
        case 2: 
            if (isLeapYear(year)) { 
                if (day > 29) return false;
                else return true;        		
            }
            else if (day > 28) return false;
            else return true;
        default:
            return true;
    }
}

inline bool Datetime::isValidTime(int hours, 
                                  int minutes, 
                                  int seconds, 
                                  int milliSeconds)
{
    if (hours == 24) {
        if ((minutes != 0) || (seconds !=0) || (milliSeconds != 0))
            return false;
        else return true;
    }
    else return (hours >= 0) && (hours < 24) && 
        (minutes >= 0) && (minutes < 60) && 
        (seconds >= 0) && (seconds < 60) &&
        (milliSeconds >= 0) && (milliSeconds < 1000);
}

} // namespace blpapi {
} // namespace BloombergLP {

#endif // #ifdef __cplusplus

#endif /* #ifndef INCLUDED_API_DATETIME */

