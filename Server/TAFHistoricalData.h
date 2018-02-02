#pragma once
#ifndef _TAFHISTORICALDATA_H
#define _TAFHISTORICALDATA_H

#include "TAFMarketData.h"

enum TAFHistoricalPeriod : int
{
	Minute = 1,
	Hour = 60,
	Day = 1440,
	Week = 10080,
	Month = 43800,
	Year = 525600
};

class TAFHistoricalPoint
{
public:
	boost::posix_time::ptime time;
	double open;
	double high;
	double low;
	double close;
	double volume;
	bool has_open;
	bool has_high;
	bool has_low;
	bool has_close;
	bool has_volume;

	TAFHistoricalPoint(boost::posix_time::ptime date);
};

class TAFHistoricalData : public TAFMarketData
{
private:
	std::vector<TAFHistoricalPoint> datapoints;
	
public:
	TAFHistoricalData(std::string ticker, boost::posix_time::ptime updatedate, TAFHistoricalPeriod period);
	std::string pack();
	TAFHistoricalPeriod period;
	int count();
	void add(TAFHistoricalPoint p);
	TAFHistoricalPoint operator [](int c);
	bool operator==(TAFHistoricalData &d);
	bool operator!=(TAFHistoricalData &d);
};

#endif