#include "../includes/ClientConnection.hpp"
#include <unistd.h> //close()
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring> //strerror()
#include <stdexcept>
#include <string>

ClientConnection::ClientConnection(int fd) : _fd(fd), _sentBytes(0) {}

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
		_requestBuffer.append(buffer, bytesRecv); //If the received data has embedded nulls (unlikely in HTTP headers but possible in POST bodies), you’ll not truncate this way
		return (bytesRecv);
	}
	if (bytesRecv == 0)
		return (0);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (-1);
	std::string	errorMsg(strerror(errno));
	throw std::runtime_error("error: recv: " + errorMsg);
}

bool	ClientConnection::completedRequest(void) //TODO
{
	//GET
	if (_requestBuffer.find("\r\n\r\n") != std::string::npos)
		return (true);

	//POST
	//if()

	//DELETE
	//if()

	return (false);
}


int const&	ClientConnection::getFD(void) const
{
	return (this->_fd);
}

size_t const&	ClientConnection::getSentBytes(void) const
{
	return (this->_sentBytes);
}

std::string const&	ClientConnection::getRequestBuffer(void) const
{
	return (_requestBuffer);
}

std::string const&	ClientConnection::getResponseBuffer(void) const
{
	return (_responseBuffer);
}

void		ClientConnection::setSentBytes(size_t bytes)
{
	this->_sentBytes = bytes;
}
