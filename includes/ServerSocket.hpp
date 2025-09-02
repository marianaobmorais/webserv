#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

//#include "ClientConnection.hpp"

class ServerSocket
{
	private:
		int				_fd;
		ServerSocket(ServerSocket const& src);
		ServerSocket&	operator=(ServerSocket const& rhs);
	public:
		ServerSocket(void);
		~ServerSocket(void);

		//accessors
		void			setFD(int newFD);

		//later
		//void			listen(/* ip, port */); //bind + listen
		//ClientConnection	accept(void); //accepts clients, producing ClientConnection
};

#endif //SERVERSOCKET_HPP