#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include "ServerSocket.hpp"
#include <vector>
#include <map>

class ClientConnection;
class WebServer
{
	private:
		//Config						_config; //probably const and reference //later
		ServerSocket					_serverSocket;
		std::map<int, ClientConnection>	_clients; //can also hold fd set to -1
		std::vector<struct pollfd>		_pollFDs;
		//bool							run; //to handle the run loop

		WebServer(WebServer const& src); //memmove?
		WebServer&						operator=(WebServer const& rhs); //memmove?
	public:
		WebServer(void);
		~WebServer(void);

		void							startServer(void);
		void							runServer(void); //run loop
		void							addToPollFD(int fd, short events);
		//void							handleRevents();
		void							removeClientConnection(int clientFD, size_t poolFDIndex);
		//later
		//void							stop(void); //cleanup
};

#endif //WEBSERVER_HPP