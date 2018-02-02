#pragma once
#ifndef _TAFMARKETDATA_H
#define _TAFMARKETDATA_H

class TAFMarketData
{
public:
	std::string ticker;
	boost::posix_time::ptime updatedate;

	TAFMarketData(std::string ticker, boost::posix_time::ptime updatedate);
	std::string pack();
	bool operator==(const TAFMarketData &d);
	bool operator!=(const TAFMarketData &d);
	~TAFMarketData(void);
};

#endif