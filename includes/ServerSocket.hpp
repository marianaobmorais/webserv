#ifndef SERVERSOCKET_HPP
# define SERVERSOCKET_HPP

//#include "ClientConnection.hpp"

class ServerSocket
{
	private:
		int				_fd; // is it const? or a reference?
		ServerSocket(ServerSocket const& src);
		ServerSocket&	operator=(ServerSocket const& rhs);
	public:
		ServerSocket(void); //should I accept non-parameterized constructor?
		ServerSocket(int newFD);
		~ServerSocket(void);

		void			listen(/* ip, port */); //bind + listen
		//ClientConnection	accept(void); //accepts clients, producing ClientConnection
};

#endif //SERVERSOCKET_HPP