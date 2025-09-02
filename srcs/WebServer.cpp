#include "WebServer.hpp"
#include <sys/socket.h> //socket(), setsockopt()
#include <netdb.h> //getaddrinfo()
#include <unistd.h> //close() //not sure if there is a C++ alternative
#include <cstring> //memset()
#include <string>
#include <exception>

WebServer::WebServer(void) : _serverSocket() {}

WebServer::~WebServer(void){}

void		WebServer::startSocket(void)
{
	int				status;
	int				socketFD;
	struct addrinfo	hints;
	struct addrinfo	*servInfo;
	struct addrinfo	*tmp;

	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; //IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; //TCP
	hints.ai_flags = AI_PASSIVE; //Fill IP for me

	if ((status = ::getaddrinfo(NULL, "8080", &hints, &servInfo )) != 0) //the "8080" service should be set by config
	{
		std::string	errorMsg(gai_strerror(status));
		::freeaddrinfo(servInfo);
		throw std::runtime_error("error: getaddrinfo: " + errorMsg);
	}
	/* getaddrinfo() returns a list of address structures.
	Try each address until we successfully bind(2).
	If socket(2) (or bind(2)) fails, we (close the socket
	and) try the next address. */
	for (tmp = servInfo; tmp != NULL; tmp = tmp->ai_next)
	{
		socketFD = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (socketFD == -1)
			continue ;
		if (bind(socketFD, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ; //sucess
		close(socketFD);
	}
	::freeaddrinfo(servInfo);
	if (socketFD == -1)
		throw std::runtime_error("error: bind: could not bind");
	int	yes = 1;
	if (::setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) != 0)
	{
		std::string	errorMsg(strerror(errno));
		throw std::runtime_error("error: setsockopt: " + errorMsg);
	}
	this->_serverSocket.setFD(socketFD);
}