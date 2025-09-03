#include "../includes/WebServer.hpp"
#include <sys/socket.h> // SOMAXCONN

WebServer::WebServer(void) : _serverSocket() {}

WebServer::~WebServer(void){}

void		WebServer::start(void)
{
	this->_serverSocket.bindSocket("8080"); //this parameter will be from config file probably
	this->_serverSocket.listenConnections(SOMAXCONN);
}

void	WebServer::run(void)
{
	while (true)
	{

	}
}
