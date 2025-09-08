#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

#include	<string>

class ClientConnection
{
	private:
		int					_fd;
		std::string			_requestBuffer;
		std::string			_responseBuffer;
		size_t				_sentBytes;
		//time_t				_lastActive;

		ClientConnection&	operator=(ClientConnection const& rhs); //memmove?
	public:
		ClientConnection(int fd);
		ClientConnection(ClientConnection const& src); //memmove?
		~ClientConnection(void);

		ssize_t				recvData(void);
		bool				completedRequest(void);

		//accessor
		int const&			getFD(void) const;
		size_t const&		getSentBytes(void) const;
		std::string const&	getRequestBuffer(void) const;
		std::string const&	getResponseBuffer(void) const;
		void				setSentBytes(size_t bytes);
		

};

#endif //CLIENTCONNECTION_HPP