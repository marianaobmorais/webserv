#include "WebServer.hpp"
#include <sys/socket.h> //socket()
#include <netdb.h> //getaddrinfo()
#include <string>

WebServer::WebServer(void) : _serverSocket(NULL) {}

WebServer::~WebServer(void){}

//start socket
void		WebServer::start(void)
{
	int	socketFD;

	socketFD = socket();

}