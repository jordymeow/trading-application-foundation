#include "StdAfx.h"
#include "TAFHistoricalData.h"

using namespace boost::gregorian;

TAFHistoricalData::TAFHistoricalData(std::string ticker, boost::posix_time::ptime updatedate, TAFHistoricalPeriod period) 
: TAFMarketData(ticker, updatedate)
{
	this->period = period;
}

std::string TAFHistoricalData::pack()
{
	std::string result = ((TAFMarketData)*this).pack();

	for (int c = 0; c < count(); c++)
	{
		result += "&H!" + boost::lexical_cast<std::string, int>(period) + "!" + to_iso_extended_string((*this)[c].time) + "!" +
		((*this)[c].has_open ? boost::lexical_cast<std::string, double>((*this)[c].open) : "") + "!" +
		((*this)[c].has_high ? boost::lexical_cast<std::string, double>((*this)[c].high) : "") + "!" +
		((*this)[c].has_low ? boost::lexical_cast<std::string, double>((*this)[c].low) : "") + "!" +
		((*this)[c].has_close ? boost::lexical_cast<std::string, double>((*this)[c].close) : "") + "!" +
		((*this)[c].has_volume ? boost::lexical_cast<std::string, double>((*this)[c].volume) : "");
	}
	return result;
}

bool TAFHistoricalData::operator==(TAFHistoricalData &d)
{
	if ((TAFMarketData)*this != (TAFMarketData)d || d.count() != count())
		return false;
	for (int c = 0; c < count(); c++)
		if (d[c].has_close != (*this)[c].has_close || d[c].close != (*this)[c].close || d[c].has_high != (*this)[c].has_high || 
			d[c].has_low != (*this)[c].has_low || d[c].has_open != (*this)[c].has_open || d[c].has_volume != (*this)[c].has_volume ||
			d[c].high != (*this)[c].high || d[c].low != (*this)[c].low || d[c].open != (*this)[c].open || d[c].volume != (*this)[c].volume)
			return false;
	return true;
}

bool TAFHistoricalData::operator!=(TAFHistoricalData &d)
{
	return !(*this == d);
}

void TAFHistoricalData::add(TAFHistoricalPoint p)
{
	datapoints.push_back(p);
}

int TAFHistoricalData::count()
{
	return datapoints.size();
}

TAFHistoricalPoint TAFHistoricalData::operator [](int c)
{
	return datapoints.at(c);
}

TAFHistoricalPoint::TAFHistoricalPoint(boost::posix_time::ptime time)
{
	this->time = time;
	has_open = has_high = has_low = has_close = has_volume = false;
}