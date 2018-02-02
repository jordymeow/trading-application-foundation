#include "stdafx.h"
#include "TAFServer.h"
#include "TAFConnection.h"
#include "TAFParadigm.h"
#include "TAFYahooFinanceParadigm.h"
#include "TAFBloombergParadigm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TAFServer::TAFServer(int port) :
	_endpoint(boost::asio::ip::tcp::v4(), port),
	_acceptor(_ioService, _endpoint), // An acceptor to accept incoming TCP connections.
	_socket(_ioService),
	_isShuttingDown(false)
	{
	}

void TAFServer::Connection_Handler(const boost::system::error_code& e)
{
	if (e)
	{
		if (!(e.value() == 995) && _isShuttingDown)
			std::cout << "S!M!" << e.message() << std::endl;
		return;
	}
	else
	{
		// Send the connection's execution on a thread
		std::cout << "New connection." << std::endl;
		
		// Asynchronous, but no thread
		_pConnection->Run();

		//TODO: Move this to the Connection class (when multithread enabled)...
		_pParadigm->Post(std::string("S!C!") + _pConnection->IPAddress());
	}
	WaitForNextClient();
}

void TAFServer::WaitForNextClient()
{
	// Wait for a next connection
	_pConnection = boost::shared_ptr<TAFConnection>(new TAFConnection(_ioService, _pParadigm, this));
	_acceptor.async_accept(_pConnection->Socket(), 
							boost::bind(&TAFServer::Connection_Handler, this, 
										ba::placeholders::error));
}

void TAFServer::Run()
{
	_pParadigm = boost::shared_ptr<TAFParadigm>(new TAFBloombergParadigm(_ioService, this));
	WaitForNextClient();
	std::cout << "Server started." << std::endl;
	_ioService.run();
}

void TAFServer::Close()
{
	_isShuttingDown = true;
	_acceptor.cancel();
}

TAFServer::~TAFServer(void)
{
	std::cout << "Server deleted." << std::endl;
}
