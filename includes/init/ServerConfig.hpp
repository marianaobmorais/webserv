#ifndef SERVER_CONFIG_HPP
# define SERVER_CONFIG_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

//Just only for test
class ServerConfig
{
	private:
		ServerConfig();
		~ServerConfig();

	public:
		static ServerConfig&	instance();

		const std::string			root;
		const std::string			index;
		const std::string			cgiPath;
		const std::string			error_page_404;
		std::vector<std::string>	allow_methods; //TODO
		//TODO client_max_body_size
		//TODO return
		bool						autoindex; //TODO
		const std::string			upload_path;
};

#endif //SERVER_CONFIG_HPP