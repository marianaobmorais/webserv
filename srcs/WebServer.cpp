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
	//time_t	now = time(NULL); //to compare with CGI start time

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

		if (ready == -1) //error
		{
			if (errno == EINTR) //"harmless/temporary error"?
				continue ;
			std::string	errorMsg(strerror(errno));
			throw std::runtime_error("error: poll: " + errorMsg);
		}
		if (ready == 0) //poll timed out
		{
			; //TODO //Check how long each CGI process has been running, remove zombie processes
		}

		for (ssize_t i = static_cast<ssize_t>(this->_pollFDs.size()) - 1; i >= 0 ; i--)  // Loop through all poll monitored FDs //Backward iteration avoids messing with indices when removing clients
		{
			//std::cout << "this->_pollFDs[i].fd: " << this->_pollFDs[i].fd << ", events: " << this->_pollFDs[i].revents << ", revents: " << this->_pollFDs[i].revents << ", errno: " << errno << std::endl; //debug

			if (this->_pollFDs[i].revents & POLLIN) //check if POLLIN bit is set, regardless of what other bits may also be set
			{
				if (this->_pollFDs[i].fd == this->_serverSocket.getFD()) // Ready on listening socket -> accept new client
					this->queueClientConnections();
				else //If it wasn’t the server socket, then it must be one of the client sockets
					this->receiveRequest(i);
			}
			else if (_pollFDs[i].revents & POLLOUT) //handle send()
			{
				//TODO
				std::map<int, ClientConnection>::iterator	it;
				it = this->_clients.find(this->_pollFDs[i].fd);
				if (it != this->_clients.end()) //should I treat it in case of false?
				{
					ClientConnection	&client = it->second;
					size_t				totalLen = client.getResponseBuffer().length();
					size_t				sent = client.getSentBytes();
					size_t				toSend = (totalLen > sent) ? (totalLen - sent) : 0;

					if (!toSend)
					{
						this->_pollFDs[i].events = POLLIN; //set revents too?
						continue ; //not sure?
					}
					
					ssize_t	bytesSent = send(client.getFD(), client.getResponseBuffer().c_str() + sent, toSend, 0);
					if (bytesSent == -1)
					{
						this->removeClientConnection(client.getFD(), i);
					}
					else
					{
						client.setSentBytes(sent + static_cast<size_t>(bytesSent));
						if (client.getSentBytes() == totalLen)
						{
							//client.clearBuffer();
							client.setSentBytes(0);
							this->_pollFDs[i].events = POLLIN; //After sending full response, switch back to POLLIN
						}
					}
				}
			}
			else if (this->_pollFDs[i].revents & (POLLERR | POLLHUP)) //POLLNVAL?
			{
				std::map<int, ClientConnection>::iterator	it;
				it = this->_clients.find(this->_pollFDs[i].fd);
				if (it != this->_clients.end())
					this->removeClientConnection(it->second.getFD(), i);
			} //if I leave this uncommented, it won't print std::cout << client.getRequestBuffer() << std::endl;
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

void	WebServer::receiveRequest(size_t i)
{
	std::map<int, ClientConnection>::iterator	it;
	it = this->_clients.find(this->_pollFDs[i].fd);
	if (it != this->_clients.end()) //should I treat it in case of false?
	{
		ClientConnection	&client = it->second;
		try
		{
			ssize_t	bytesRecv = client.recvData();

			if (bytesRecv > 0)
			{
				if (client.completedRequest())
				{
					std::cout << client.getRequestBuffer() << std::endl;
					//TODO
				}
			}
			else if (bytesRecv == 0)
				this->removeClientConnection(client.getFD(), i);
		}
		catch (std::exception const& e)
		{
			std::cerr << "error: " << e.what() << '\n';
			this->removeClientConnection(client.getFD(), i);
		}
	}
}

void	WebServer::removeClientConnection(int clientFD, size_t pollFDIndex)
{
	std::cout << "Closing client fd=" << clientFD << std::endl;
	std::cout << "removing client connection..." << std::endl;
	this->_clients.erase(clientFD); //erase by key // the clientConnection destructor already handles close the fd -> RAII
	this->_pollFDs.erase(_pollFDs.begin() + pollFDIndex); //erase by iterator position
}

void	WebServer::addToPollFD(int fd, short events)
{
	struct pollfd	pollFD;
	pollFD.fd = fd;
	pollFD.events = events;
	pollFD.revents = 0;
	this->_pollFDs.push_back(pollFD);
}
