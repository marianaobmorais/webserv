#include "../includes/WebServer.hpp"
#include <sys/socket.h> // SOMAXCONN
#include <cstring>
#include <errno.h>
#include <poll.h>
#include <stdexcept>
#include <iostream>

WebServer::WebServer(void) : _serverSocket() {}

WebServer::~WebServer(void){}

void		WebServer::start(void)
{
	this->_serverSocket.bindSocket("8080"); //this parameter will be from config file probably
	this->_serverSocket.listenConnections(SOMAXCONN);
}

void	WebServer::run(void)
{
	//should I put this bit in the start method?
	struct pollfd	serverPollFD;
	serverPollFD.fd = this->_serverSocket.getFD();
	serverPollFD.events = POLLIN; // monitor for incoming connections
	serverPollFD.revents = 0;
	this->_pollFDs.push_back(serverPollFD); // the server's listening socket is always the first [0], the client ones start from index 1

	while (true)
	{
		if (::poll(&this->_pollFDs[0], this->_pollFDs.size(), -1) == -1) //-1 means it won't time out
		{
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg);
		}

		for (size_t i = 0; i < this->_pollFDs.size(); i++)  // Loop through all monitored FDs
		{
			if (this->_pollFDs[i].revents & POLLIN)
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
				{
					try
					{
						ClientConnection	newClient = this->_serverSocket.acceptConnections();
						int					newClientFD = newClient.getFD();
						this->_clients.insert(std::make_pair(newClientFD, newClient));

						//Add to pollFDs
						struct pollfd	newPollFD;
						newPollFD.fd = newClientFD;
						newPollFD.events = POLLIN; // monitor for incoming data
						newPollFD.revents = 0;
						this->_pollFDs.push_back(newPollFD);
					}
					catch(const std::exception& e)
					{
						std::cerr << e.what() << '\n';
					}
				}
			}
			else
			{
				//will do later
				//Existing client has data
				std::cout << "Client FD " << this->_pollFDs[i].fd << " has data ready" << std::endl;
			}
		}
	}
}
