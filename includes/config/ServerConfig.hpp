#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

#include <LocationConfig.hpp>
#include <string>
#include <vector>

class ServerConfig
{
	private:
		std::string					_listenPort;
		//std::vector<int>			_listenPort; //In Nginx-like configs, a server block can listen on multiple ports or IPs
		std::string					_serverName; // "example.com" -> same as hostname?
		std::string					_root; //The server block root sets the document root for the whole server
		std::vector<LocationConfig>	_locations;

		ServerConfig(ServerConfig const& src);
		ServerConfig&				operator=(ServerConfig const& rhs);
	public:
		ServerConfig(void);
		~ServerConfig(void);

		//accessors
		std::string const&			getListenPort(void) const;
};

#endif //SERVERCONFIG_HPP