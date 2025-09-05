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

void	WebServer::start(void)
{
	this->_serverSocket.bindSocket("8080"); //this parameter will be from config file probably
	this->_serverSocket.listenConnections(SOMAXCONN);

	//start _pollFDs vector
	// the server's listening socket is always the first [0], the client ones start from index 1
	this->addToPollFD(this->_serverSocket.getFD(), POLLIN); // monitor for incoming connections
}

void	WebServer::run(void)
{
	while (true)
	{
		if (::poll(&this->_pollFDs[0], this->_pollFDs.size(), -1) == -1) //-1 means it won't time out
		{
			if (errno == EINTR) //are there other "harmless/temporary errors"?
				continue ;
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg);
		}

		//std::cout << "clients: " << _clients.size() << " pollFDs: " << _pollFDs.size() << std::endl; //debug

		for (size_t i = 0; i < this->_pollFDs.size(); i++)  // Loop through all monitored FDs
		{
			if (this->_pollFDs[i].revents & POLLIN) //check if POLLIN bit is set, regardless of what other bits may also be set
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
				{
					std::vector<int>	newFDs = this->_serverSocket.acceptConnections(); //accepts the connections
					for (size_t j = 0; j < newFDs.size(); j++)
					{
						int	newClientFD = newFDs[j];
						if (_clients.find(newClientFD) == _clients.end()) //avoid duplicates
						{
							this->_clients.insert(std::make_pair(newClientFD, ClientConnection(newClientFD))); //should I create a method that saves the client object in _clients?
							//std::cout << "populate client map with fd: " << newClientFD << std::endl; //debug

							//Add to pollFDs //adds the client’s file descriptor to _pollFDs so poll() will also monitor it
							this->addToPollFD(newClientFD, POLLIN);
						}
					}
				}
				else //If it wasn’t the server socket, then it must be one of the client sockets
				{
					//std::cout << "Try to read data from fd: " << _pollFDs[i].fd << std::endl; //debug

					std::map<int, ClientConnection>::iterator	it;
					it = this->_clients.find(_pollFDs[i].fd);
					if (it != this->_clients.end()) //I don't understand this check //is there a chance that this check is false?
					{
						ClientConnection	&client = it->second;
						try
						{
							ssize_t				bytesRecv = client.recvData();

							if (bytesRecv > 0)
							{
								if (client.completedRequest())
									//std::cout << "Handle HTTP parse" << std::endl; //TODO
									std::cout << client.getRecvBuffer() << std::endl;
							}
							else if (bytesRecv == 0)
							{
								this->removeClientConnection(client.getFD(), i);
								i--;
							}
						}
						catch (std::exception const& e)
						{
							std::cerr << e.what() << '\n'; //error
							this->removeClientConnection(client.getFD(), i);
							i--;
						}
					}
				}
			}
			else //!(this->_pollFDs[i].revents & POLLIN)
			{
				; //later //how to handle resizing of this->_pollFDs?
			}
		}
	}
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
