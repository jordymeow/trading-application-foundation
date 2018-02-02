#pragma once 
#ifndef _TAFSERVER_H
#define _TAFSERVER_H

class TAFConnection;
class TAFParadigm;

// Class noncopyable is a base class.
// Derive your own class from noncopyable when you want to
// prohibit copy construction and copy assignment.

class TAFServer : private boost::noncopyable, public boost::enable_shared_from_this<TAFServer>
{

public:
	TAFServer(int port = 1982);
	~TAFServer(void);

	void Run();
	void Close();

private: 
	// The io_service represents the program's link to the operating system's I/O services. 
	ba::io_service _ioService;
	ba::ip::tcp::endpoint _endpoint;
	ba::ip::tcp::acceptor _acceptor;
	ba::ip::tcp::socket _socket;
	//boost::thread_group _threads;
	std::map<boost::shared_ptr<TAFConnection>, boost::thread *> _connectionToThread;
	boost::shared_ptr<TAFConnection> _pConnection;
	boost::shared_ptr<TAFParadigm> _pParadigm;
	bool _isShuttingDown;

	void WaitForNextClient();
	void Connection_Handler(const boost::system::error_code& e);
};

#endif