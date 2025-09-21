#include <init/ServerConfig.hpp>

ServerConfig::ServerConfig() : root("/home/jose/webserv_42/var/www/html"),
	index("index.html"),
	cgiPath("/bin/python3.py"),
	error_page_404("errors/404.html"),
	autoindex(true)
{}

ServerConfig::~ServerConfig() {}

ServerConfig&	ServerConfig::instance()
{
	static ServerConfig serverConfig;
	return (serverConfig);
}
