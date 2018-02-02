#include "stdafx.h"
#include "TAFParadigm.h"
#include "TAFServer.h"
#include "TAFConnection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

TAFParadigm::TAFParadigm(ba::io_service& ioService, TAFServer *server) :
	_ioService(ioService)
{
	_server = server;
}

// Post the message to all the connections
void TAFParadigm::Post(const std::string message, boost::shared_ptr<TAFConnection> sender)
{
	std::string final = (sender != NULL ? (sender->IPAddress() + std::string(" -> ")) 
		: std::string("")) + message + "\r\n";

	for (std::list<boost::shared_ptr<TAFConnection>>::iterator it = _connections.begin(); 
		it != _connections.end(); it++)
	{
		if (*it != sender)
			it->get()->Send(final);
	}
}

void TAFParadigm::Join(boost::shared_ptr<TAFConnection> connection)
{
	_connections.push_back(connection);	
}

void TAFParadigm::Leave(boost::shared_ptr<TAFConnection> connection)
{
	_connections.remove(connection);
}


TAFParadigm::~TAFParadigm(void)
{
	_connections.clear();
	std::cout << "Paradigm (default) deleted." << std::endl;
}
