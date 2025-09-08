#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

#include <string>
#include <vector>
#include "ClientConnection.hpp"

class ServerSocket
{
	private:
		int					_fd;

		ServerSocket(ServerSocket const& src); //memmove?
		ServerSocket&					operator=(ServerSocket const& rhs); //memmove?
	public:
		ServerSocket(void);
		~ServerSocket(void);

		void				startSocket(std::string const& port);
		void				listenConnections(int backlog);
		std::vector<int>	acceptConnections(void);
		//std::vector<ClientConnection>	acceptConnections(void); //accepts clients, producing a vector of ClientConnection

		//accesor
		int const&			getFD(void) const;
};

#endif //SERVERSOCKET_HPP