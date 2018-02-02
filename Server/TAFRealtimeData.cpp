#include "StdAfx.h"
#include "TAFRealtimeData.h"

TAFRealtimeData::TAFRealtimeData(std::string ticker, boost::posix_time::ptime updatedate) 
: TAFMarketData(ticker, updatedate)
{
	has_last = false;
	has_high = false;
	has_low = false;
	has_volume = false;
	has_open = false;
	has_change = false;
	has_bid = false;
	has_ask = false;
}

std::string TAFRealtimeData::pack()
{
	return ((TAFMarketData)*this).pack() + "&R!" +
		(has_last ? boost::lexical_cast<std::string, double>(last) : "") + "!" +
		(has_high ? boost::lexical_cast<std::string, double>(high) : "") + "!" +
		(has_low ? boost::lexical_cast<std::string, double>(low) : "") + "!" +
		(has_volume ? boost::lexical_cast<std::string, double>(volume) : "") + "!" +
		(has_open ? boost::lexical_cast<std::string, double>(open) : "") + "!" +
		(has_change ? boost::lexical_cast<std::string, double>(change) : "") + "!" +
		(has_bid ? boost::lexical_cast<std::string, double>(bid) : "") + "!" +
		(has_ask ? boost::lexical_cast<std::string, double>(ask) : "");
}

bool TAFRealtimeData::operator==(TAFRealtimeData &d)
{
	if (d.has_last == has_last && d.last == last && d.has_change == has_change && d.has_high == has_high && 
		d.has_low == has_low && d.has_open == has_open && d.has_volume == has_volume && d.has_bid == has_bid && d.has_ask == has_ask
		&& d.change == change && d.high == high && d.low == low && d.open == open && d.volume == volume && d.bid == bid && d.ask == ask)
		return (TAFMarketData)*this == (TAFMarketData)d;
	else
		return false;
}

bool TAFRealtimeData::operator!=(TAFRealtimeData &d)
{
	return !(*this == d);
}

TAFRealtimeData::~TAFRealtimeData(void)
{
}
