#pragma once
#include "TAFParadigm.h"

class TAFMarketData;
class TAFRealtimeData;
class TAFHistoricalData;

class TAFYahooFinanceParadigm : public TAFParadigm
{
public:
	TAFYahooFinanceParadigm(ba::io_service& ioService, TAFServer *server);
	~TAFYahooFinanceParadigm(void);

	virtual void Post(const std::string message, boost::shared_ptr<TAFConnection> sender = boost::shared_ptr<TAFConnection>());

private:
	bool _stopRequested;
	boost::thread_group _threads;
	std::map<std::string, TAFRealtimeData> _tickerToValue;
	std::map<std::string, int> _tickerToFails;
	std::queue<std::string> _tickersQueue;
	std::queue<std::string> _instantRequestsQueue;
	boost::mutex _queueMutex;

	void ThreadedLoopForRealtime(int startIn);
	void ThreadedLoopForInstant();
	std::string PopNextTicker();
	std::string YahooRequest(const std::string &ticker);
	void ExecuteNextRequest(std::string ticker);
	void AddTicker(const std::string ticker);
	void RemoveTicker(const std::string ticker);

	TAFRealtimeData ConvertToRealtimeData(const std::string buffer);
	TAFHistoricalData ConvertToHistoricalData(const std::string ticker, const std::string buffer);
};
