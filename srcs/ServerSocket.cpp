#include "../includes/ServerSocket.hpp"
#include <sys/socket.h> //socket(), setsockopt(), listen()
#include <netdb.h> //getaddrinfo()
#include <unistd.h> //close() //not sure if there is a C++ alternative
#include <cstring> //memset()
#include <unistd.h>
#include <exception>
#include <string>

ServerSocket::ServerSocket(void) : _fd(-1) {}

ServerSocket::~ServerSocket(void)
{
	if (this->_fd != -1)
		::close(this->_fd);
}

void	ServerSocket::bindSocket(std::string const& port)
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

	if ((status = ::getaddrinfo(NULL, port.c_str(), &hints, &servInfo )) != 0)
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
		socketFD = ::socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (socketFD == -1)
			continue ;
		int	yes = 1;
		::setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)); //check if != 0? or leave it to the check if (socketFD == -1)?
		if (::bind(socketFD, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ; //sucess
		::close(socketFD);
		socketFD = -1;
	}
	::freeaddrinfo(servInfo);
	if (socketFD == -1)
		throw std::runtime_error("error: bind: fail to bind");
	this->_fd = socketFD;
}

void	ServerSocket::listenConnections(int backlog)
{
	if (::listen(this->_fd, backlog) == -1)
	{
		std::string	errorMsg(strerror(errno));
		throw std::runtime_error("listen: listenConnections: " + errorMsg);
	}
}

ClientConnection	ServerSocket::acceptConnections(void)
{
	struct sockaddr_storage	clientAddr;
	socklen_t				addrSize;
	int						clientFD;

	addrSize = sizeof(clientAddr);
	clientFD = accept(this->_fd, (struct sockaddr*)&clientAddr, &addrSize);
	if (clientFD == -1)
	{
		std::string	errorMsg(strerror(errno));
		throw std::runtime_error("error: accept: " + errorMsg);
	}
	return (ClientConnection(clientFD));
}