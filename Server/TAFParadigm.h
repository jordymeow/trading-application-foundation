#pragma once
#ifndef _TAFPARADIGM_H
#define _TAFPARADIGM_H

class TAFServer;
class TAFConnection;

// A paradigm represents a defined environment for a Connection. Example of paradigms:
// Bloomberg Paradigm (to retrieve realtime market data)
// Automation X Paradigm (to subscribe to Automaton X events + to send commands)

// A Connection can be part of 1+ paradigm(s).

// TAFParadigm is the base class for all the paradigms.

class TAFParadigm : public boost::enable_shared_from_this<TAFParadigm>
{

public:
	TAFParadigm(ba::io_service& ioService, TAFServer *server);
	~TAFParadigm(void);

	virtual void Join(boost::shared_ptr<TAFConnection> connection);
	virtual void Leave(boost::shared_ptr<TAFConnection> connection);
	virtual void Post(const std::string message, boost::shared_ptr<TAFConnection> sender = boost::shared_ptr<TAFConnection>());

protected:
	ba::io_service &_ioService;
	std::list<boost::shared_ptr<TAFConnection>> _connections;
	TAFServer *_server;
};

#endif
