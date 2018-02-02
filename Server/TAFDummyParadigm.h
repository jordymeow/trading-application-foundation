#pragma once
#include "TAFParadigm.h"

class TAFMarketData;
class TAFRealtimeData;
class TAFHistoricalData;

class TAFDummyParadigm  : public TAFParadigm
{
public:
	TAFDummyParadigm(ba::io_service& ioService, TAFServer *server);
	~TAFDummyParadigm(void);

	virtual void Post(const std::string message, boost::shared_ptr<TAFConnection> sender = boost::shared_ptr<TAFConnection>());
};
