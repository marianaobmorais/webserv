#include "../includes/ClientConnection.hpp"
#include <unistd.h> //close()
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring> //strerror()
#include <stdexcept>
#include <string>

ClientConnection::ClientConnection(int fd) : _fd(fd) {}

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