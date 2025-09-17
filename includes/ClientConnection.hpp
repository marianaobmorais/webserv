#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

#include <string>
#include <sys/types.h>


class ClientConnection
{
	private:
		int					_fd;
		std::string			_requestBuffer;
		std::string			_responseBuffer;
		size_t				_sentBytes;
		//time_t				_lastActive;
		//httpresquet
		//httpresponse

		ClientConnection&	operator=(ClientConnection const& rhs); //memmove?
	public:
		ClientConnection(int fd);
		ClientConnection(ClientConnection const& src); //memmove?
		~ClientConnection(void);

		ssize_t				recvData(void);
		ssize_t				sendData(ClientConnection &client, size_t sent, size_t toSend);
		bool				completedRequest(void);
		void				clearBuffer(void);

		//accessors
		int const&			getFD(void) const;
		size_t const&		getSentBytes(void) const;
		std::string const&	getRequestBuffer(void) const;
		std::string const&	getResponseBuffer(void) const;
		void				setSentBytes(size_t bytes);
		void				setResponseBuffer(std::string buffer);
};

#endif //CLIENTCONNECTION_HPP