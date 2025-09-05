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

ssize_t	ClientConnection::recvData(void)
{
	if (_fd == -1)
	{
		throw std::runtime_error("error: recvData: fd == -1");
	}

	char	buffer[1024]; //4096?
	ssize_t	bytesRecv;

	bytesRecv = ::recv(this->_fd, buffer, sizeof(buffer), 0);
	if (bytesRecv > 0)
	{
		_recvBuffer.append(buffer, bytesRecv); //If the received data has embedded nulls (unlikely in HTTP headers but possible in POST bodies), you’ll not truncate this way
		return (bytesRecv);
	}
	if (bytesRecv == 0)
		return (0);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (-1);
	std::string	errorMsg(strerror(errno));
	throw std::runtime_error("error: recv: " + errorMsg);
}

bool	ClientConnection::completedRequest(void)
{
	//I will also get at least POST and DELETE requests
	return (_recvBuffer.find("\r\n\r\n") != std::string::npos);
}


int	ClientConnection::getFD(void)
{
	return (this->_fd);
}

std::string	ClientConnection::getRecvBuffer(void)
{
	return (_recvBuffer);
}
