#include "stdafx.h"
#include "TAFYahooFinanceParadigm.h"
#include "TAFServer.h"
#include "TAFConnection.h"
#include "TAFMarketData.h"
#include "TAFRealtimeData.h"
#include "TAFHistoricalData.h"
#include "TAFBloombergParadigm.h"

namespace 
{
    const Name SECURITY_DATA("securityData");
    const Name SECURITY("security");
    const Name FIELD_DATA("fieldData");
    const Name RESPONSE_ERROR("responseError");
    const Name SECURITY_ERROR("securityError");
    const Name FIELD_EXCEPTIONS("fieldExceptions");
    const Name FIELD_ID("fieldId");
    const Name ERROR_INFO("errorInfo");
    const Name CATEGORY("category");
    const Name MESSAGE("message");
    const Name SESSION_TERMINATED("SessionTerminated");
    const Name SESSION_STARTUP_FAILURE("SessionStartupFailure");
	const Name EXCEPTIONS("exceptions");
    const Name REASON("reason");
    const Name DESCRIPTION("description");
	const Name ERRORCODE("errorCode");
	const Name BAR_DATA("barData");
    const Name BAR_TICK_DATA("barTickData");
	const Name OPEN("open");
    const Name HIGH("high");
    const Name LOW("low");
    const Name CLOSE("close");
    const Name VOLUME("volume");
    const Name NUM_EVENTS("numEvents");
    const Name TIME("time");
}

static boost::regex regex_historicalrequest("%([A-Z=. ]*)!([0-9]{4})([0-9]{2})([0-9]{2})!([0-9]{4})([0-9]{2})([0-9]{2})!([A-Z]{1,2})");

TAFBloombergParadigm::TAFBloombergParadigm(ba::io_service& ioService, TAFServer *server) : TAFParadigm(ioService, server)
{
	_stopRequested = false;
	_host = "localhost";
    _port = 8194;
    _maxEvents = INT_MAX;
    _eventCount = 0;
	SessionOptions sessionOptions;
    sessionOptions.setServerHost(_host.c_str());
    sessionOptions.setServerPort(_port); 
	_session = boost::shared_ptr<Session>(new Session(sessionOptions));
	std::cout << "Bloomberg: Opening a session..." << std::endl;
	if (!_session->start()) 
	{
		throw std::exception("Bloomberg: failed to start the session.");
		return;
	}
	std::cout << "Bloomberg: Session opened." << std::endl;
	std::cout << "Bloomberg: Opening the realtime service..." << std::endl;
	if (!_session->openService("//blp/mktdata")) 
	{
		throw std::exception("Bloomberg: failed to open //blp/mktdata.");
		return;
    }
	std::cout << "Bloomberg: Realtime service active." << std::endl;
	std::cout << "Bloomberg: Opening the referential service..." << std::endl;
	if (!_session->openService("//blp/refdata")) 
	{
		throw std::exception("Bloomberg: failed to open //blp/refdata.");
		return;
    }
	_refService = _session->getService("//blp/refdata");
	std::cout << "Bloomberg: Referential service active." << std::endl;
	_threads.create_thread(boost::bind(&TAFBloombergParadigm::ThreadedLoop, this));
	std::cout << "Bloomberg: Active." << std::endl;
}

void TAFBloombergParadigm::ThreadedLoop()
{
	while (!_stopRequested) 
	{
		Event event = _session->nextEvent();
		MessageIterator msgIter(event);
		while (msgIter.next()) 
		{
			Message msg = msgIter.message();
			if (event.eventType() == Event::SUBSCRIPTION_STATUS)
			{
				// The subscription has failed or has been canceled..
				if (msg.hasElement(REASON))
					ConvertReason(msg);
			}
			else if (event.eventType() == Event::PARTIAL_RESPONSE || event.eventType() == Event::RESPONSE) 
			{
				if (event.eventType() == Event::PARTIAL_RESPONSE)
				{
					std::cout << "Bloomberg: Oops, we need to implement more here...!" << std::endl;
					msg.print(std::cout) << std::endl;
				}
				int topic = (int)msg.correlationId().asInteger();
				std::map<int, std::string>::iterator it = _cidToTicker.lower_bound(topic);
				if (it != _cidToTicker.end() && !(_cidToTicker.key_comp()(topic, it->first)))
				{
					std::map<int, int>::iterator it2 = _cidToPeriod.lower_bound(topic);
					if (it2 != _cidToPeriod.end() && !(_cidToPeriod.key_comp()(topic, it2->first)))
					{
						TAFHistoricalData data = ConvertToHistoricalData(msg, it->second, it2->second);
						TAFParadigm::Post(data.pack());
						_cidToTicker.erase(topic);
						_cidToPeriod.erase(topic);
					}
				}
            }
			else if (event.eventType() == Event::SUBSCRIPTION_DATA)
			{
				int topic = (int)msg.correlationId().asInteger();
				std::map<int, std::string>::iterator it = _cidToTicker.lower_bound(topic);
				if (it != _cidToTicker.end() && !(_cidToTicker.key_comp()(topic, it->first)))
				{
					TAFRealtimeData data = ConvertToRealtimeData(msg, it->second);
					TAFParadigm::Post(data.pack());
				}
			}
			else
			{
				msg.print(std::cout) << std::endl;
			}
		}
	}
}

void TAFBloombergParadigm::ConvertReason(Message &msg)
{
	Element reason = msg.getElement(REASON);
	// Subscription has an error (if errorcode == 0 it's actually an unsubscription)
	if (reason.hasElement(ERRORCODE) && reason.getElementAsInt32(ERRORCODE) != 0)
	{
		int topic = (int)msg.correlationId().asInteger();
		std::string ticker = "";
		std::map<int, std::string>::iterator it = _cidToTicker.lower_bound(topic);
		if (it != _cidToTicker.end() && !(_cidToTicker.key_comp()(topic, it->first)))
		{
			ticker = it->second;
			TAFParadigm::Post(("F!") + it->second);
			RemoveTicker(it->second);
		}
		std::cout << "Bloomberg: " << reason.getElementAsString(DESCRIPTION) << " (" << ticker << ")" << std::endl;
	}
}

TAFHistoricalData TAFBloombergParadigm::ConvertToHistoricalData(Message &msg, std::string ticker, int period)
{
	TAFHistoricalData data(ticker, boost::posix_time::second_clock::local_time(), (TAFHistoricalPeriod)period);

	Element d = msg.getElement(BAR_DATA).getElement(BAR_TICK_DATA);
    int numBars = d.numValues();
    for (int i = 0; i < numBars; ++i) 
	{
		Element bar = d.getValueAsElement(i);
		Datetime bbgDate = bar.getElementAsDatetime(TIME);
		boost::posix_time::ptime t(boost::gregorian::date(bbgDate.year(), bbgDate.month(), bbgDate.day()), 
			boost::posix_time::time_duration(bbgDate.hours(), bbgDate.minutes(), bbgDate.seconds()));
		TAFHistoricalPoint p(t);
		if (bar.hasElement(OPEN, true))
		{
			p.has_open = true;
			p.open = bar.getElementAsFloat64(OPEN);
		}
		if (bar.hasElement(HIGH, true))
		{
			p.has_high = true;
			p.high = bar.getElementAsFloat64(HIGH);
		}
		if (bar.hasElement(LOW, true))
		{
			p.has_low = true;
			p.low = bar.getElementAsFloat64(LOW);
		}
		if (bar.hasElement(CLOSE, true))
		{
			p.has_close = true;
			p.close = bar.getElementAsFloat64(CLOSE);
		}
		if (bar.hasElement(VOLUME, true))
		{
			p.has_volume = true;
			p.volume = bar.getElementAsInt64(VOLUME);
		}
		data.add(p);
	}
	return data;
}

TAFRealtimeData TAFBloombergParadigm::ConvertToRealtimeData(Message &msg, std::string ticker)
{
	Datetime bbgTime;
	if (msg.hasElement("EVENT_TIME"))
		bbgTime = msg.getElementAsDatetime("EVENT_TIME");
	else if (msg.hasElement("TIME"))
		bbgTime = msg.getElementAsDatetime("TIME");
	else
		msg.print(std::cout) << std::endl;
	boost::posix_time::ptime t;
	if (msg.hasElement("TRADING_DT_REALTIME"))
	{
		Datetime bbgDate = msg.getElementAsDatetime("TRADING_DT_REALTIME");
		t = boost::posix_time::ptime(boost::gregorian::date(bbgDate.year(), bbgDate.month(), bbgDate.day()), 
			boost::posix_time::time_duration(bbgTime.hours(), bbgTime.minutes(), bbgTime.seconds()));
	}
	else
	{
		
		boost::gregorian::date d = boost::posix_time::second_clock::local_time().date();
		t = boost::posix_time::ptime(boost::gregorian::date(d.year(), d.month(), d.day()), 
			boost::posix_time::time_duration(bbgTime.hours(), bbgTime.minutes(), bbgTime.seconds()));
	}

	TAFRealtimeData data(ticker, t);

	if (msg.hasElement("LAST_PRICE", true))
	{
		data.last = msg.getElementAsFloat64("LAST_PRICE");
		data.has_last = true;
	}
	if (msg.hasElement("BID", true))
	{
		data.bid = msg.getElementAsFloat64("BID");
		data.has_bid = true;
	}
	if (msg.hasElement("ASK", true))
	{
		data.ask = msg.getElementAsFloat64("ASK");
		data.has_ask = true;
	}
	if (msg.hasElement("RT_PX_CHG_PCT_1D", true))
	{
		data.change = msg.getElementAsFloat64("RT_PX_CHG_PCT_1D");
		data.change = true;
	}
	if (msg.hasElement("OPEN", true))
	{
		data.open = msg.getElementAsFloat64("OPEN");
		data.has_open = true;
	}
	if (msg.hasElement("HIGH", true))
	{
		data.high = msg.getElementAsFloat64("HIGH");
		data.has_high = true;
	}
	if (msg.hasElement("LOW", true))
	{
		data.low = msg.getElementAsFloat64("LOW");
		data.has_low = true;
	}
	if (msg.hasElement("VOLUME", true))
	{
		data.volume = msg.getElementAsFloat64("VOLUME");
		data.has_volume = true;
	}
	return data;
}

// +GOOG : Realtime subscription to Google stock
// !GOOG!2009!10!25!2009!12!25!D : History request for the Google stock
// (T = tick, H = hour, D = daily, W = weekly, M = monthly)

void TAFBloombergParadigm::AddTicker(const std::string ticker)
{
	std::map<std::string, int>::iterator it = _tickerToCid.lower_bound(ticker);
	if (!(it != _tickerToCid.end() && !(_tickerToCid.key_comp()(ticker, it->first))))
	{
		std::map<int, std::string>::iterator it2 = _cidToTicker.lower_bound(_eventCount);
		_cidToTicker.insert(it2, std::map<int, std::string>::value_type(_eventCount, ticker));
		_tickerToCid.insert(it, std::map<std::string, int>::value_type(ticker, _eventCount));
		SubscriptionList subscriptions;
		subscriptions.add(ticker.c_str(), "LAST_PRICE,BID,ASK", "", CorrelationId(_eventCount++));
		_session->subscribe(subscriptions);
	}
	else
	{
	}
}

void TAFBloombergParadigm::RemoveTicker(const std::string ticker)
{
	std::map<std::string, int>::iterator it = _tickerToCid.lower_bound(ticker);
	if (it != _tickerToCid.end() && !(_tickerToCid.key_comp()(ticker, it->first)))
	{
		SubscriptionList subscriptions;
		subscriptions.add(it->second);
		_session->unsubscribe(subscriptions);
		_cidToTicker.erase(it->second);
		_tickerToCid.erase(ticker);
	}
}

void TAFBloombergParadigm::HistoryRequest(std::string ticker, int yearFrom, int monthFrom, int dayFrom,
										  int yearTo, int monthTo, int dayTo, std::string period)
{
	Request request = _refService.createRequest("IntradayBarRequest");

    request.set("security", ticker.c_str());
    request.set("eventType", "TRADE");
	request.set("interval", period == "HH" ? Hour : period == "MM" ? Minute : period == "M" ? Month : period == "W" ? Week : Day);
	Datetime from, to;
	from.setYear(yearFrom);
	from.setMonth(monthFrom);
	from.setDay(dayFrom);
	to.setYear(yearTo);
	to.setMonth(monthTo);
	to.setDay(dayTo);
	request.set("startDateTime", from);
	request.set("endDateTime", to);
    request.set("gapFillInitialBar", false);

	std::map<int, std::string>::iterator it = _cidToTicker.lower_bound(_eventCount);
	_cidToTicker.insert(it, std::map<int, std::string>::value_type(_eventCount, ticker));

	int p = period == "HH" ? Hour : period == "MM" ? Minute : period == "M" ? Month : period == "W" ? Week : Day;
	std::map<int, int>::iterator it2 = _cidToPeriod.lower_bound(_eventCount);
	_cidToPeriod.insert(it2, std::map<int, int>::value_type(_eventCount, p));

    _session->sendRequest(request, CorrelationId(_eventCount++));
}

void TAFBloombergParadigm::Post(const std::string message, boost::shared_ptr<TAFConnection> sender)
{
	if (message.length() > 1 && message.at(0) == '+')
		AddTicker(std::string((const char *)(message.c_str() + 1)));
	else if (message.length() > 1 && message.at(0) == '-')
		RemoveTicker(std::string((const char *)(message.c_str() + 1)));
	else if (message.length() > 1 && message.at(0) == '%')
	{
		boost::smatch what;
		if (boost::regex_match(message, what, regex_historicalrequest))
		{
			std::string ticker = what[1];
			std::string period = what[8];
			int yearFrom = boost::lexical_cast<int, std::string>(what[2]);
			int monthFrom = boost::lexical_cast<int, std::string>(what[3]);
			int dayFrom = boost::lexical_cast<int, std::string>(what[4]);
			int yearTo = boost::lexical_cast<int, std::string>(what[5]);
			int monthTo = boost::lexical_cast<int, std::string>(what[6]);
			int dayTo = boost::lexical_cast<int, std::string>(what[7]);
			HistoryRequest(ticker, yearFrom, monthFrom, dayFrom, yearTo, monthTo, dayTo, period);
		}
	}
	else
		TAFParadigm::Post(std::string(message), sender);
}

TAFBloombergParadigm::~TAFBloombergParadigm(void)
{
	std::cout << "Shutting down Bloomberg paradigm..." << std::endl;
	std::cout << "Bloomberg paradigm deleted." << std::endl;
}