#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include <ServerSocket.hpp>
#include <config/ServerConfig.hpp>
#include <vector>
#include <map>

class ClientConnection;
class Config;
class WebServer
{
	private:
		std::vector<ServerConfig>		_config;
		std::map<int, size_t>			_FDToConfig; // FD to index in _config
		//std::vector<ServerSocket>		_serverSocket;

		ServerSocket					_serverSocket; //vector
		std::map<int, ClientConnection>	_clients; //can also hold fd set to -1
		std::vector<struct pollfd>		_pollFDs;
		//bool							run; //to handle the run loop

		WebServer(WebServer const& src); //memmove?
		WebServer&						operator=(WebServer const& rhs); //memmove?
	public:
		WebServer(Config const& config);
		~WebServer(void);

		void							startServer(void);
		void							runServer(void); //run loop
		void							queueClientConnections(void);
		void							addToPollFD(int fd, short events);
		void							receiveRequest(std::size_t i);
		void							sendResponse(std::size_t i);
		void							removeClientConnection(int clientFD, size_t pollFDIndex);
		//later
		//void							stop(void); //cleanup
};

#endif //WEBSERVER_HPP