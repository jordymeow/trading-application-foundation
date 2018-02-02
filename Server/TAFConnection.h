#pragma once
#ifndef _TAFCONNECTION_H
#define _TAFCONNECTION_H

#include "TAFParadigm.h"

// "enabled_shared_from_this" is used as a base class that allows a shared_ptr
// to the current object to be obtained from within a member function. 

class TAFConnection : public boost::enable_shared_from_this<TAFConnection>
{

public:
	TAFConnection(ba::io_service& ioService, boost::shared_ptr<TAFParadigm>, TAFServer *server);
	~TAFConnection(void);

	ba::ip::tcp::socket& Socket() 
	{
        return _socket;
    }

	const std::string IPAddress() 
	{
        return _ipAddress;
    }

	void Send(const std::string message);
	void Run();
	void Close();

private:
	ba::io_service &_ioService;
	ba::ip::tcp::socket _socket;
	std::string _ipAddress;
	std::string _currentMessage;
	ba::streambuf buf;
	boost::shared_ptr<TAFParadigm> _paradigm;
	TAFServer *_server;

	void Read_Handler(const boost::system::error_code& error, size_t bytes_transferred);
	void Write_Handler(const boost::system::error_code& error, size_t bytes_transferred);
	void WaitForNextMessage();
};

#endif