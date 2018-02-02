#pragma once
#include "TAFParadigm.h"

class TAFMarketData;
class TAFRealtimeData;
class TAFHistoricalData;

using namespace BloombergLP;
using namespace blpapi;

class TAFBloombergParadigm  : public TAFParadigm
{
public:
	TAFBloombergParadigm(ba::io_service& ioService, TAFServer *server);
	~TAFBloombergParadigm(void);

	virtual void Post(const std::string message, boost::shared_ptr<TAFConnection> sender = boost::shared_ptr<TAFConnection>());

private:
	bool _stopRequested;
	std::string _host;
    int _port;
    int _maxEvents;
    int _eventCount;
	boost::thread_group _threads;
	boost::shared_ptr<Session> _session;
	Service _refService;

	std::map<int, std::string> _cidToTicker;
	std::map<int, int> _cidToPeriod;
	std::map<std::string, int> _tickerToCid;

	TAFRealtimeData ConvertToRealtimeData(Message &msg, std::string ticker);
	TAFHistoricalData ConvertToHistoricalData(Message &msg, std::string ticker, int period);
	void ConvertReason(Message &msg);
	void HistoryRequest(std::string ticker, int yearFrom, int monthFrom, int dayFrom, int yearTo, int monthTo, int dayTo, std::string period);
	void AddTicker(const std::string ticker);
	void RemoveTicker(const std::string ticker);
	void ThreadedLoop();
};
