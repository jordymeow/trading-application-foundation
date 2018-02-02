#include "StdAfx.h"
#include "TAFMarketData.h"

using namespace boost::gregorian;

TAFMarketData::TAFMarketData(std::string ticker, boost::posix_time::ptime updatedate)
{
	this->ticker = ticker;
	this->updatedate = updatedate;
}

std::string TAFMarketData::pack()
{
	return "D!" + ticker + "!" + to_iso_extended_string(updatedate);
}

bool TAFMarketData::operator==(const TAFMarketData &d)
{
	if (d.ticker == ticker && d.updatedate == updatedate)
		return true;
	else
		return false;
}

bool TAFMarketData::operator!=(const TAFMarketData &d)
{
	return !(*this == d);
}

TAFMarketData::~TAFMarketData(void)
{
}
