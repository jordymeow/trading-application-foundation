#include "stdafx.h"
#include "TAFConnection.h"
#include "TAFServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TAFConnection::TAFConnection(ba::io_service& ioService, boost::shared_ptr<TAFParadigm> paradigm, TAFServer *server) :
	_ioService(ioService),
	_socket(ioService),
	_paradigm(paradigm),
	_server(server)
{
}

void TAFConnection::Run()
{
	ba::ip::tcp::endpoint remote_ep = _socket.remote_endpoint();
	ba::ip::address remote_ad = remote_ep.address();
	_ipAddress = remote_ad.to_string();
	WaitForNextMessage();
	_paradigm->Join(this->shared_from_this());
}

void TAFConnection::WaitForNextMessage()
{
	// Read until a "\r\n" is found
	ba::async_read_until(_socket, buf, boost::regex("\r\n"),
						 boost::bind(&TAFConnection::Read_Handler, this->shared_from_this(),
									 ba::placeholders::error,
									 ba::placeholders::bytes_transferred));
}

void TAFConnection::Read_Handler(const boost::system::error_code& e, size_t bytes_transferred)
{
	if (e)
	{
		if (e == boost::asio::error::eof)
		{
			Close();
			return;
		}
		else if (e.value() != 995)
		{
			std::cout << "Err: " << e.message() << std::endl;
			Close();
			return;
		}
	}
	else
	{
		// Get the current line
		std::istream is(&buf);
		std::string line;
		std::getline(is, line);
		line.erase(line.size() - 1, 1);
		std::cout << "Received: " << line << std::endl;
		// Exit command
		if (strcmp(line.c_str(), "exit") == 0)
		{
			Close();
			return;
		}
		// Kill command
		if (strcmp(line.c_str(), "kill") == 0)
		{
			Close();
			_server->Close();
			return;
		}
		_paradigm->Post(std::string(line), shared_from_this());
	}
	WaitForNextMessage();
}

void TAFConnection::Send(const std::string message)
{
	_currentMessage = message;
	ba::async_write(_socket, ba::buffer(_currentMessage),
                        boost::bind(&TAFConnection::Write_Handler, this->shared_from_this(),
                                    ba::placeholders::error,
                                    ba::placeholders::bytes_transferred));
}

void TAFConnection::Write_Handler(const boost::system::error_code& e, size_t bytes_transferred) 
{
	if (e)
	{
		std::cout << "Err: " << e.message() << std::endl;
		Close();
	}
}

void TAFConnection::Close()
{
	_paradigm->Leave(shared_from_this());
	_socket.close();
	shared_from_this().reset();
	std::cout << "Connection closed." << std::endl;
}

TAFConnection::~TAFConnection(void)
{
	std::cout << "Connection deleted." << std::endl;
}
