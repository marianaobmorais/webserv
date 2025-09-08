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
	
	//time_t	now = time(NULL); //to compare with CGI start time
	return (10000); //10 seconds
}
//

void	WebServer::runServer(void)
{
	while (true)
	{
		int timeout = getPollTimeout(false); //update poll() timeout parameter accordingly to the presence of CGI process
		int	ready = ::poll(&this->_pollFDs[0], this->_pollFDs.size(), timeout);

		if (ready == -1) //error
		{
			if (errno == EINTR) //"harmless/temporary error"?
				continue ;
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg);
		}
		if (ready == 0) //poll timed out
		{
			//TODO //Check how long each CGI process has been running, remove zombie processes
		}

		std::cout << "debug: _pollFDs.size() = " << _pollFDs.size() << std::endl; //debug
		for (size_t i = 0; i < this->_pollFDs.size(); /* i++ */)  // Loop through all poll monitored FDs
		{
			if (this->_pollFDs[i].revents & (POLLERR | POLLHUP | POLLNVAL) && this->_pollFDs[i].fd != this->_serverSocket.getFD()) // Fatal conditions -> remove client
			{
				std::cout << "POLLERROR fd=" << _pollFDs[i].fd << " errno=" << errno << std::endl; //debug
				this->removeClientConnection(this->_pollFDs[i].fd, i);
				continue ;
			}

			if (this->_pollFDs[i].revents & POLLIN) //check if POLLIN bit is set, regardless of what other bits may also be set
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
					this->queueClientConnections();
				else //If it wasn’t the server socket, then it must be one of the client sockets
				{
					//receive request
					std::map<int, ClientConnection>::iterator	it;
					it = this->_clients.find(this->_pollFDs[i].fd);
					if (it != this->_clients.end())
					{
						ClientConnection	&client = it->second;
						try
						{
							ssize_t	bytesRecv = client.recvData();
							if (bytesRecv > 0 && client.completedRequest())
							{
									std::cout << client.getRequestBuffer() << std::endl; //debug: why is it not printing the request anymore?
									//TODO: build HTTP response
									// client.setResponseBuffer(buildHTTPResponse(client));
									client.setSentBytes(0);
									this->_pollFDs[i].events = POLLOUT; //After receiving a full request, switch events to POLLOUT
							}
							else if (bytesRecv == 0) //client closed
							{
								this->removeClientConnection(client.getFD(), i);
								continue ;
							}
							else if (bytesRecv == -1)
							{
								this->_pollFDs.erase(this->_pollFDs.begin() + i);
								continue ;
							}
						}
						catch (std::exception const& e)
						{
							std::cerr << "error: " << e.what() << '\n';
							this->removeClientConnection(client.getFD(), i);
							continue;
						}
					}
				}
			}
			else if (_pollFDs[i].revents & POLLOUT) //send response
			{
				std::map<int, ClientConnection>::iterator	it;
				it = this->_clients.find(_pollFDs[i].fd);
				if (it != this->_clients.end())
				{
					ClientConnection	&client = it->second;
					size_t				total = client.getResponseBuffer().size();
					size_t				sent = client.getSentBytes();
					size_t				toSend = (total > sent) ? (total - sent) : 0;

					if (toSend > 0)
					{

						ssize_t				bytesSent = send(client.getFD(), client.getResponseBuffer().c_str() + sent, toSend, 0);

						if (bytesSent <= 0)
						{
							this->removeClientConnection(client.getFD(), i);
							continue ;
						}
						client.setSentBytes(sent + static_cast<size_t>(bytesSent));
					}
					if (client.getSentBytes() == total)
					{
						//TODO
						//client.clearResponseBuffer();
						client.setSentBytes(0);
						this->_pollFDs[i].events = POLLIN; //After sending full response, switch back to POLLIN
					}
				}
				else //not sure if it will ever go in here
				{
					this->_pollFDs.erase(_pollFDs.begin() + i);
					continue ;
				}
			}
			this->_pollFDs[i].revents = 0; // reset after processing
			++i; // increment only if we didn't erase
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
	std::cout << "queueClientConnections: newFDs.size()=" << newFDs.size() << std::endl; //debug

}

// bool	WebServer::receiveRequest(size_t i)
// {
// 	std::map<int, ClientConnection>::iterator	it;
// 	it = this->_clients.find(_pollFDs[i].fd);
// 	if (it != this->_clients.end())
// 	{
// 		ClientConnection	&client = it->second;
// 		try
// 		{
// 			ssize_t	bytesRecv = client.recvData();

// 			if (bytesRecv > 0)
// 			{
// 				if (client.completedRequest())
// 					std::cout << client.getRecvBuffer() << std::endl; //TODO
// 			}
// 			else if (bytesRecv == 0)
// 			{
// 				this->removeClientConnection(client.getFD(), i);
// 				return (false);
// 			}
// 		}
// 		catch (std::exception const& e)
// 		{
// 			std::cerr << "error: " << e.what() << '\n';
// 			this->removeClientConnection(client.getFD(), i);
// 			return (false);
// 		}
// 		return (true);
// 	}
// 	return (false);
// }

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
