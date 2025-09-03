#ifndef CLIENTCONNECTION_HPP
# define CLIENTCONNECTION_HPP

class ClientConnection
{
	private:
		int					_fd;
		ClientConnection(ClientConnection const& src);
		ClientConnection&	operator=(ClientConnection const& rhs);
	public:
		ClientConnection(int fd);
		~ClientConnection(void);
};

#endif //CLIENTCONNECTION_HPP