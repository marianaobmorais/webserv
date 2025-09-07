#include "../includes/WebServer.hpp"
#include <sys/socket.h> // SOMAXCONN
#include <unistd.h> //close()
#include <errno.h>
#include <poll.h>
#include <cstring>
#include <stdexcept>
#include <iostream>

WebServer::WebServer(void) : _serverSocket() {}

WebServer::~WebServer(void){}

void	WebServer::startServer(void)
{
	this->_serverSocket.startSocket("8080"); //this parameter will be from config file probably
	this->_serverSocket.listenConnections(SOMAXCONN);

	//start _pollFDs vector
	// the server's listening socket is always the first [0], the client ones start from index 1
	this->addToPollFD(this->_serverSocket.getFD(), POLLIN); // monitor for incoming connections
}

//HELPER FUNCTION
static int	getPollTimeout(bool CGI) //refactor later
{
	if (!CGI)
		return (-1); //no timeout
	else
		return (10000); //10 seconds
}
//

void	WebServer::runServer(void)
{
	while (true)
	{
		int timeout = getPollTimeout(false); //update poll() timeout parameter accordingly to the presence of CGI process
		int	ready = ::poll(&this->_pollFDs[0], this->_pollFDs.size(), timeout);
		//time_t	now = time(NULL); //to compare with CGI start time

		if (ready == -1) //error
		{
			// if (errno == EINTR) //"harmless/temporary error"?
			// 	continue ;
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg);
		}
		if (ready == 0) //poll timed out
		{
			//TODO //Check how long each CGI process has been running, remove zombie processes
		}

		const size_t	readySize = this->_pollFDs.size();
		for (size_t i = 0; i < readySize; i++)  // Loop through all poll monitored FDs
		{
			if (this->_pollFDs[i].revents & POLLIN) //check if POLLIN bit is set, regardless of what other bits may also be set
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
					this->queueClientConnections();
				else //If it wasn’t the server socket, then it must be one of the client sockets
				{
					if (!this->receiveRequest(i))
						i--;
				}
			}
			else
			{
				if (_pollFDs[i].revents & POLLOUT) //handle send()
					; //TODO
				else
					;
			}
		}
	}
}

void	WebServer::queueClientConnections(void)
{
	std::vector<int>	newFDs = this->_serverSocket.acceptConnections(); //accepts the connections
	for (size_t j = 0; j < newFDs.size(); j++)
	{
		int	newClientFD = newFDs[j];
		if (_clients.find(newClientFD) == _clients.end()) //avoid adding duplicates
		{
			//new client connection
			this->_clients.insert(std::make_pair(newClientFD, ClientConnection(newClientFD)));

			//Add to pollFDs //adds the client’s file descriptor to _pollFDs so poll() will also monitor it
			this->addToPollFD(newClientFD, POLLIN);
		}
	}
}

bool	WebServer::receiveRequest(size_t i)
{
	std::map<int, ClientConnection>::iterator	it;
	it = this->_clients.find(_pollFDs[i].fd);
	if (it != this->_clients.end())
	{
		ClientConnection	&client = it->second;
		try
		{
			ssize_t	bytesRecv = client.recvData();

			if (bytesRecv > 0)
			{
				if (client.completedRequest())
					std::cout << client.getRecvBuffer() << std::endl; //TODO
			}
			else if (bytesRecv == 0)
			{
				this->removeClientConnection(client.getFD(), i);
				return (false);
			}
		}
		catch (std::exception const& e)
		{
			std::cerr << "error: " << e.what() << '\n';
			this->removeClientConnection(client.getFD(), i);
			return (false);
		}
		return (true);
	}
	return (false);
}

void	WebServer::removeClientConnection(int clientFD, size_t poolFDIndex)
{
	this->_clients.erase(clientFD); //erase by key // the clientConnection destructor already handles close the fd -> RAII
	this->_pollFDs.erase(_pollFDs.begin() + poolFDIndex); //erase by iterator position
}

void	WebServer::addToPollFD(int fd, short events)
{
	struct pollfd	pollFD;
	pollFD.fd = fd;
	pollFD.events = events;
	pollFD.revents = 0;
	this->_pollFDs.push_back(pollFD);
}
