#include "stdafx.h"
#include "TAFYahooFinanceParadigm.h"
#include "TAFServer.h"
#include "TAFConnection.h"
#include "TAFMarketData.h"
#include "TAFRealtimeData.h"
#include "TAFHistoricalData.h"
#include <boost/algorithm/string.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace boost::gregorian;

static boost::regex regex_historicalrequest("%([A-Z=.]*)!([0-9]{4})([0-9]{2})([0-9]{2})!([0-9]{4})([0-9]{2})([0-9]{2})!([A-Z]{1,2})");
static boost::regex regex_historical("([0-9]{4})-([0-9]{1,2})-(([0-9]{1,2})|N/A),(([0-9.-]*)|N/A),(([0-9.-]*)|N/A),(([0-9.-]*)|N/A),(([0-9.-]*)|N/A),(([0-9]*)|N/A),(([0-9.-]*)|N/A)");
static boost::regex regex_realtime("\"([A-Z\.=]*)\",(([0-9.-]*)|(N/A)),\"([0-9]{1,2})/([0-9]{1,2})/([0-9]{4})\",\"([0-9]{1,2}):([0-9]{1,2})(am|pm)\",(([0-9.-]*)|(N/A)),(([0-9.-]*)|(N/A)),(([0-9.-]*)|(N/A)),(([0-9.-]*)|(N/A)),(([0-9]*)|(N/A))\r\n");

// HTTP request to Yahoo, for both historical or static/realtime requests
std::string TAFYahooFinanceParadigm::YahooRequest(const std::string &ticker)
{
		try
		{
			boost::asio::io_service io_service;
			ba::ip::tcp::resolver resolver(io_service);
			ba::ip::tcp::resolver::query query("download.finance.yahoo.com", "http");
			boost::smatch what;
			std::string str;

			if (ticker.at(0) != '%' && ticker.at(0) != '$')
				str = std::string("/d/quotes.csv?s=") + ticker + std::string("&f=sl1d1t1c1ohgv");
			else if (boost::regex_match(ticker, what, regex_historicalrequest))
			{
				int i_month_from = boost::lexical_cast<int, std::string>(what[3]);
				int i_month_to = boost::lexical_cast<int, std::string>(what[6]);
				std::string month_from = boost::lexical_cast<std::string, int>(i_month_from - 1);
				std::string month_to = boost::lexical_cast<std::string, int>(i_month_to - 1);

				query = ba::ip::tcp::resolver::query("ichart.finance.yahoo.com", "http");
				str = std::string("/table.csv?s=") + what[1] + std::string("&c=") + what[2] + std::string("&a=") + month_from 
					+ std::string("&b=") + what[4] + std::string("&f=") + what[5] + std::string("&d=") + month_to
						+ std::string("&e=") + what[7] + std::string("&g=") + (what[8] == "M" ? "m" : what[8] == "W" ? "w" : "d");
			}
			else
			{
				TAFParadigm::Post(("F! ") + ticker);
				return "";
			}
			 
			ba::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			ba::ip::tcp::resolver::iterator end;
			ba::ip::tcp::socket socket(io_service);
			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && endpoint_iterator != end)
			{
			  socket.close();
			  socket.connect(*endpoint_iterator++, error);
			}
			if (error)
			  throw boost::system::system_error(error);
			boost::asio::streambuf request;	
			std::ostream request_stream(&request);
			if (ticker.at(0) != '!')
			{
				request_stream	<< "GET " << str << " HTTP/1.0\r\n" 
								<< "Host: " << "download.finance.yahoo.com" << "\r\n" 
								<< "Accept: */*\r\n"
								<< "Connection: close\r\n\r\n";
			}
			else
			{
				request_stream	<< "GET " << str << " HTTP/1.0\r\n" 
								<< "Host: " << "ichart.finance.yahoo.com" << "\r\n" 
								<< "Accept: */*\r\n"
								<< "Connection: close\r\n\r\n";
			}
			boost::asio::write(socket, request);
			boost::asio::streambuf response;
			boost::asio::read_until(socket, response, "\r\n");
			std::istream response_stream(&response);
			std::string http_version;
			response_stream >> http_version;
			unsigned int status_code;
			response_stream >> status_code;
			std::string status_message;
			std::getline(response_stream, status_message);
			if (!response_stream || http_version.substr(0, 5) != "HTTP/" || status_code != 200)
				return "";
			boost::asio::read_until(socket, response, "\r\n\r\n");
			std::string header;
			while (std::getline(response_stream, header) && header != "\r");
			std::ostringstream ss;

			ss << &response;

			while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
					ss << &response;;

			std::string buffer = ss.str();
			return buffer;
		}
	  catch (std::exception& e)
	  {
		std::cout << "Exception: " << e.what() << std::endl;
		return "";
	  }
}

// Get next ticker in the queue (for realtime)
std::string TAFYahooFinanceParadigm::PopNextTicker()
{
	boost::mutex::scoped_lock lock(_queueMutex);
	std::string ticker = _tickersQueue.front();
	_tickersQueue.pop();
	std::map<std::string, TAFRealtimeData>::iterator it = _tickerToValue.lower_bound(ticker);
	while (!(it != _tickerToValue.end() && !(_tickerToValue.key_comp()(ticker, it->first))))
	{
		if (_tickersQueue.size() > 0)
		{
			ticker = _tickersQueue.front();
			_tickersQueue.pop();
			_tickerToValue.lower_bound(ticker);
		}
		else
			return std::string();
	}
	return ticker;
}

// Convert a Yahoo reply into a TAFRealtimeData
TAFRealtimeData TAFYahooFinanceParadigm::ConvertToRealtimeData(std::string buffer)
{
	boost::smatch what;

	if (boost::regex_match(buffer, what, regex_realtime))
	{
		boost::posix_time::ptime t(boost::posix_time::from_iso_string(what[7] + what[5] + what[6] + "T000000"));
		t += boost::posix_time::hours(std::atoi(((std::string)what[8]).c_str()) + (what[10] == "pm" ? 12 : 0)) + boost::posix_time::minutes(std::atoi(((std::string)what[9]).c_str()));

		TAFRealtimeData data(what[1], t);

		if (what[2] != "N/A")
		{
			data.last = boost::lexical_cast<double, std::string>(what[2]);
			data.has_last = true;
		}
		if (what[11] != "N/A")
		{
			data.change = (boost::lexical_cast<double, std::string>(what[11]));
			data.has_change = true;
		}
		if (what[14] != "N/A")
		{
			data.open = (boost::lexical_cast<double, std::string>(what[14]));
			data.has_open = true;
		}
		if (what[17] != "N/A")
		{
			data.high = (boost::lexical_cast<double, std::string>(what[17]));
			data.has_high = true;
		}
		if (what[20] != "N/A")
		{
			data.low = (boost::lexical_cast<double, std::string>(what[20]));
			data.has_low = true;
		}
		if (what[23] != "N/A")
		{
			data.volume = boost::lexical_cast<double, std::string>(what[23]);
			data.has_volume = true;
		}
		return data;
	}
	throw std::exception("Yahoo reply cannot be converted to TAFRealtimeData");
}

// Convert a Yahoo reply into a TAFRealtimeData
TAFHistoricalData TAFYahooFinanceParadigm::ConvertToHistoricalData(const std::string request, const std::string buffer)
{
	boost::smatch whatTicker;
	
	if (boost::regex_match(request, whatTicker, regex_historicalrequest))
	{
		boost::smatch what;
		std::string::const_iterator start, end;
		TAFHistoricalData data(whatTicker[1], boost::posix_time::second_clock::local_time(), whatTicker[1] == "M" ? Month : whatTicker[1] == "W" ? Week : Day);

		start = buffer.begin();
		end = buffer.end();
		while (boost::regex_search(start, end, what, regex_historical))
		{
			boost::posix_time::ptime t(boost::posix_time::from_iso_string(what[1] + what[2] + what[3] + "T000000"));
			TAFHistoricalPoint p(t);
			if (what[5] != "N/A")
			{
				p.open = boost::lexical_cast<double, std::string>(what[5]);
				p.has_open = true;
			}
			if (what[7] != "N/A")
			{
				p.high = boost::lexical_cast<double, std::string>(what[7]);
				p.has_high = true;
			}
			if (what[9] != "N/A")
			{
				p.low = boost::lexical_cast<double, std::string>(what[9]);
				p.has_low = true;
			}
			if (what[11] != "N/A")
			{
				p.close = boost::lexical_cast<double, std::string>(what[11]);
				p.has_close = true;
			}
			if (what[13] != "N/A")
			{
				p.volume = boost::lexical_cast<double, std::string>(what[13]);
				p.has_volume = true;
			}
			data.add(p);

			// Next match in the reply
			start = what[0].second;
		}
		return data;
	}
	throw std::exception("Yahoo reply cannot be converted to TAFHistoricalData");
}

void TAFYahooFinanceParadigm::ExecuteNextRequest(std::string ticker)
{
	std::string buffer = "";
	try
	{
		buffer = YahooRequest(ticker);
		if (buffer != "")
		{
			TAFRealtimeData data = ConvertToRealtimeData(buffer);
			std::map<std::string, TAFRealtimeData>::iterator it = _tickerToValue.lower_bound(ticker);
			if (it != _tickerToValue.end() && !(_tickerToValue.key_comp()(ticker, it->first)))
			{
				// Checks if the value changed since the last time
				if (it->second != data)
				{
					it->second = data;
					TAFParadigm::Post(data.pack());
				}
				
			}
			else
				return;
		}
	}
	catch (std::exception &e)
	{
		buffer = "";
		std::cerr << e.what() << std::endl;
		std::cerr << "This ticker failed: " << ticker << std::endl;
	}

	// Checks the number of fails for this ticker, and if it exceeds 3, kills it
	std::map<std::string, int>::iterator itFails = _tickerToFails.lower_bound(ticker);
	if (itFails != _tickerToFails.end() && !(_tickerToFails.key_comp()(ticker, itFails->first)))
	{

		if (buffer == "" && ++itFails->second > 2)
		{
			TAFParadigm::Post(("F!") + ticker);
			RemoveTicker(ticker);
			return;
		}
		else if (buffer != "" && itFails->second > 0)
			itFails->second = 0;
	}
	boost::mutex::scoped_lock lock(_queueMutex);
	_tickersQueue.push(ticker);
}

void TAFYahooFinanceParadigm::ThreadedLoopForRealtime(int startIn)
{
	boost::this_thread::sleep(boost::posix_time::seconds(startIn));
	while (!_stopRequested)
	{
		if (_tickersQueue.size() > 0)
		{
			std::string ticker = PopNextTicker();
			if (!ticker.empty())
				ExecuteNextRequest(ticker);
		}
		boost::this_thread::sleep(boost::posix_time::seconds(6));
	}
}

void TAFYahooFinanceParadigm::ThreadedLoopForInstant()
{
	while (!_stopRequested)
	{
		if (_instantRequestsQueue.size() > 0)
		{
			std::string request = _instantRequestsQueue.front();
			_instantRequestsQueue.pop();
			std::string buffer = YahooRequest(request);
			if (buffer.length() == 0)
				TAFParadigm::Post(("F!") + request);
			else
			{
				TAFHistoricalData data = ConvertToHistoricalData(request, buffer);
				TAFParadigm::Post(data.pack());
			}

		}
		boost::this_thread::sleep(boost::posix_time::seconds(1));
	}
}

TAFYahooFinanceParadigm::TAFYahooFinanceParadigm(ba::io_service& ioService, TAFServer *server) : TAFParadigm(ioService, server)
{
	_stopRequested = false;
	_threads.create_thread(boost::bind(&TAFYahooFinanceParadigm::ThreadedLoopForInstant, this));
	_threads.create_thread(boost::bind(&TAFYahooFinanceParadigm::ThreadedLoopForRealtime, this, 3));
	_threads.create_thread(boost::bind(&TAFYahooFinanceParadigm::ThreadedLoopForRealtime, this, 5));
}

void TAFYahooFinanceParadigm::AddTicker(const std::string ticker)
{
	std::map<std::string, TAFRealtimeData>::iterator it = _tickerToValue.lower_bound(ticker);
	if (!(it != _tickerToValue.end() && !(_tickerToValue.key_comp()(ticker, it->first))))
	{
		std::map<std::string, int>::iterator itFails = _tickerToFails.lower_bound(ticker);
		_tickerToFails.insert(itFails, std::map<std::string, int>::value_type(ticker, 0));
		_tickerToValue.insert(it, std::map<std::string, TAFRealtimeData>::value_type(ticker, TAFRealtimeData("", boost::posix_time::second_clock::local_time())));
		boost::mutex::scoped_lock lock(_queueMutex);
		_tickersQueue.push(ticker);
	}
	else
	{
		std::map<std::string, TAFRealtimeData>::iterator it = _tickerToValue.lower_bound(ticker);
		if (it != _tickerToValue.end() && !(_tickerToValue.key_comp()(ticker, it->first)) && it->second.has_last)
			TAFParadigm::Post(it->second.pack());
	}
}

void TAFYahooFinanceParadigm::RemoveTicker(const std::string ticker)
{
	boost::mutex::scoped_lock lock(_queueMutex);
	_tickerToValue.erase(ticker);
	_tickerToFails.erase(ticker);
}

// +GOOG : Realtime subscription to Google stock
// !GOOG!2009!10!25!2009!12!25!D : History request for the Google stock
// (T = tick, H = hour, D = daily, W = weekly, M = monthly)
void TAFYahooFinanceParadigm::Post(const std::string message, boost::shared_ptr<TAFConnection> sender)
{
	if (message.length() > 1 && message.at(0) == '+')
		AddTicker(std::string((const char *)(message.c_str() + 1)));
	else if (message.length() > 1 && message.at(0) == '-')
		RemoveTicker(std::string((const char *)(message.c_str() + 1)));
	else if (message.length() > 1 && message.at(0) == '%')
		_instantRequestsQueue.push(std::string((const char *)(message.c_str())));
	else
		TAFParadigm::Post(std::string(message), sender);
}

TAFYahooFinanceParadigm::~TAFYahooFinanceParadigm(void)
{
	std::cout << "Shutting down Yahoo Finance paradigm..." << std::endl;
	_stopRequested = true;
	_threads.join_all();
	std::cout << "Yahoo Finance paradigm deleted." << std::endl;
}
