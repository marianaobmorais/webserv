#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

#include <string>
#include "ClientConnection.hpp"

class ServerSocket
{
	private:
		int					_fd;

		ServerSocket(ServerSocket const& src);
		ServerSocket&		operator=(ServerSocket const& rhs);
	public:
		ServerSocket(void);
		~ServerSocket(void);

		void				bindSocket(std::string const& port);
		void				listenConnections(int backlog);
		ClientConnection	acceptConnections(void); //accepts clients, producing ClientConnection

		//accesor
		int				getFD(void);
};

#endif //SERVERSOCKET_HPP