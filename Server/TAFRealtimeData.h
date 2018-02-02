#pragma once
#ifndef _TAFREALTIMEDATA_H
#define _TAFREALTIMEDATA_H

#include "TAFMarketData.h"

class TAFRealtimeData : public TAFMarketData
{
public:
	double last;
	double bid;
	double ask;
	double high;
	double low;
	double volume;
	double open;
	double change;
	
	bool has_last;
	bool has_bid;
	bool has_ask;
	bool has_high;
	bool has_low;
	bool has_volume;
	bool has_open;
	bool has_change;

	TAFRealtimeData(std::string ticker, boost::posix_time::ptime updatedate);
	std::string pack();

	bool operator==(TAFRealtimeData &d);
	bool operator!=(TAFRealtimeData &d);
	~TAFRealtimeData(void);
};

#endif