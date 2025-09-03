#include "../includes/ClientConnection.hpp"
#include <unistd.h> //close() 

ClientConnection::ClientConnection(int fd) : _fd(fd) {}

ClientConnection::~ClientConnection(void)
{
	if (this->_fd != -1)
		::close(this->_fd);
}