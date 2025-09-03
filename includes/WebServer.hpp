#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include "ServerSocket.hpp"
#include <vector>

class ClientConnection;
class WebServer
{
	private:
		//Config						_config; //probably const and reference //later
		ServerSocket					_serverSocket;
		std::vector<ClientConnection>	_clients;

		WebServer(WebServer const& src);
		WebServer&						operator=(WebServer const& rhs);
	public:
		WebServer(void);
		~WebServer(void);

		void						start(void);
		void						run(void); //run loop
		//later
		//void						stop(void); //cleanup
};

#endif //WEBSERVER_HPP