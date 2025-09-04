#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

#include <string>
#include <vector>
#include "ClientConnection.hpp"

class ServerSocket
{
	private:
		int								_fd;

		ServerSocket(ServerSocket const& src);
		ServerSocket&					operator=(ServerSocket const& rhs);
	public:
		ServerSocket(void);
		~ServerSocket(void);

		void							bindSocket(std::string const& port);
		void							listenConnections(int backlog);
		std::vector<ClientConnection>	acceptConnections(void); //accepts clients, producing a vector of ClientConnection

		//accesor
		int								getFD(void);
};

#endif //SERVERSOCKET_HPP