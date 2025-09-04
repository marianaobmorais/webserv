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

	//start _pollFDs vector
	struct pollfd	serverPollFD;
	serverPollFD.fd = this->_serverSocket.getFD();
	serverPollFD.events = POLLIN; // monitor for incoming connections
	serverPollFD.revents = 0;
	this->_pollFDs.push_back(serverPollFD); // the server's listening socket is always the first [0], the client ones start from index 1
}

void	WebServer::run(void)
{
	while (true)
	{
		if (::poll(&this->_pollFDs[0], this->_pollFDs.size(), -1) == -1) //-1 means it won't time out
		{
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg); //continue ; to keep the server alive on temporary errors like EINTR or throw?
		}

		for (size_t i = 0; i < this->_pollFDs.size(); i++)  // Loop through all monitored FDs
		{
			//later: handle resize of this->_pollFDs here?
			if (this->_pollFDs[i].revents & POLLIN) //POLLIN bit is set, regardless of what other bits may also be se
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
				{
					std::vector<int>	newFDs = this->_serverSocket.acceptConnections(); //accepts the connections
					for (size_t j = 0; j < newFDs.size(); j++)
					{
						int	newClientFD = newFDs[j];
						this->_clients.insert(std::make_pair(newClientFD, ClientConnection(newClientFD))); // saves the client object in _clients

						//Add to pollFDs
						struct pollfd	newPollFD;
						newPollFD.fd = newClientFD;
						newPollFD.events = POLLIN; // monitor for incoming data
						newPollFD.revents = 0;
						this->_pollFDs.push_back(newPollFD); //adds the client’s file descriptor to _pollFDs so poll() will also monitor it
					}
				}
				else //If it wasn’t the server socket, then it must be one of the client sockets
				{
					//will do later //read
					//Existing client has data
					std::cout << "Client FD " << this->_pollFDs[i].fd << " has data ready" << std::endl;
				}
			}
			else //!(this->_pollFDs[i].revents & POLLIN)
			{
				//later //how to handle resizing of this->_pollFDs?
			}
		}
	}
}
