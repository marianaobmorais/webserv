#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

#include	<string>

class ClientConnection
{
	private:
		int					_fd;
		std::string			_requestBuffer;
		std::string			_responseBuffer;
		//time_t				_lastActive;

		ClientConnection&	operator=(ClientConnection const& rhs); //memmove?
	public:
		ClientConnection(int fd);
		ClientConnection(ClientConnection const& src); //memmove?
		~ClientConnection(void);

		ssize_t				recvData(void);
		bool				completedRequest(void);

		//accessor
		int					getFD(void);
		std::string			getRequestBuffer(void);
};

#endif //CLIENTCONNECTION_HPP