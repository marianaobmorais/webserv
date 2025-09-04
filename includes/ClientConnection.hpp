#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

class ClientConnection
{
	private:
		int					_fd;
		std::string			_readBuffer;
		std::string			_writeBuffer;
		//time_t				_lastActive;

		ClientConnection&	operator=(ClientConnection const& rhs);
	public:
		ClientConnection(int fd);
		ClientConnection(ClientConnection const& src);
		~ClientConnection(void);

		//accessor
		int					getFD(void);
};

#endif //CLIENTCONNECTION_HPP