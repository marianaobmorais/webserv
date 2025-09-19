#ifndef SERVER_CONFIG_HPP
# define SERVER_CONFIG_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

//Just only for test
class ServerConfig
{
	private:
		ServerConfig();
		~ServerConfig();

	public:
		static ServerConfig&	instance();

		const std::string		root;
		const std::string		index;
		const std::string		cgiPath;
};

#endif //SERVER_CONFIG_HPP