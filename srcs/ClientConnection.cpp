#include "../includes/ClientConnection.hpp"
#include <unistd.h> //close()
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring> //strerror()
#include <stdexcept>
#include <string>

//Set client sockets to non-blocking too. The new fd you get from accept() may not 
//inherit non-blocking on all platforms. After accept(), call fcntl(clientFD, F_SETFL, O_NONBLOCK) 
//(or have your ClientConnection do it in its constructor).
ClientConnection::ClientConnection(int fd) : _fd(fd)
{
	int	clientFD;

	if (::fcntl(clientFD, F_SETFL, O_NONBLOCK) == -1)
	{
		::close(clientFD);
		std::string	errorMsg(strerror(errno));
		throw std::runtime_error("error: fcntl: " + errorMsg);
	}
}

ClientConnection::ClientConnection(ClientConnection const& src) : _fd(src._fd) {}

ClientConnection::~ClientConnection(void)
{
	if (this->_fd != -1)
		::close(this->_fd);
}

int	ClientConnection::getFD(void)
{
	return (this->_fd);
}