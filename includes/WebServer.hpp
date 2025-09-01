#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

#include "ServerSocket.hpp"

class WebServer
{
	private:
		ServerSocket	_serverSocket; //const? reference?
		WebServer(WebServer const& src);
		WebServer&	operator=(WebServer const& rhs);
	public:
		WebServer(void);
		~WebServer(void);

		void		start(void); //start socket
		//void	run(void); //run loop
		//void	stop(void); //cleanup?
};

#endif //WEBSERVER_HPP