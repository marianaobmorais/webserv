#include "ServerSocket.hpp"
#include <unistd.h>

ServerSocket::ServerSocket(void) : _fd(-1) {}

ServerSocket::~ServerSocket(void)
{
	if (this->_fd != -1)
		::close(this->_fd);
}

void	ServerSocket::setFD(int newFD)
{
	this->_fd = newFD;
}
