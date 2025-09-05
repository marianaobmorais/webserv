#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

#include	<string>

class ClientConnection
{
	private:
		int					_fd;
		std::string			_recvBuffer;
		std::string			_sendBuffer;
		//time_t				_lastActive;

		ClientConnection&	operator=(ClientConnection const& rhs);
	public:
		ClientConnection(int fd);
		ClientConnection(ClientConnection const& src);
		~ClientConnection(void);

		ssize_t				recvData(void);
		bool				completedRequest(void);

		//accessor
		int					getFD(void);
		std::string			getRecvBuffer(void);
};

#endif //CLIENTCONNECTION_HPP