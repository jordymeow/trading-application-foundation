#include "stdafx.h"
#include "TAFYahooFinanceParadigm.h"
#include "TAFServer.h"
#include "TAFConnection.h"
#include "TAFMarketData.h"
#include "TAFRealtimeData.h"
#include "TAFHistoricalData.h"
#include "TAFDummyParadigm.h"

TAFDummyParadigm::TAFDummyParadigm(ba::io_service& ioService, TAFServer *server) : TAFParadigm(ioService, server)
{
}

// +GOOG : Realtime subscription to Google stock
// !GOOG!2009!10!25!2009!12!25!D : History request for the Google stock
// (T = tick, H = hour, D = daily, W = weekly, M = monthly)
void TAFDummyParadigm::Post(const std::string message, boost::shared_ptr<TAFConnection> sender)
{




	//if (message.length() > 1 && message.at(0) == '+')
	//	AddTicker(std::string((const char *)(message.c_str() + 1)));
	//else if (message.length() > 1 && message.at(0) == '-')
	//	RemoveTicker(std::string((const char *)(message.c_str() + 1)));
	//else if (message.length() > 1 && message.at(0) == '%')
	//	_instantRequestsQueue.push(std::string((const char *)(message.c_str())));
	//else
	//	TAFParadigm::Post(std::string(message), sender);
}

TAFDummyParadigm::~TAFDummyParadigm(void)
{
	std::cout << "Shutting down Bloomberg paradigm..." << std::endl;
	std::cout << "Bloomberg paradigm deleted." << std::endl;
}