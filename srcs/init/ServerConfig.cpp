#include <init/ServerConfig.hpp>

ServerConfig::ServerConfig() : root("/home/jose/webserv_42/var/www/html"), index("index.html"), cgiPath("al") {}

ServerConfig::~ServerConfig() {}

ServerConfig&	ServerConfig::instance()
{
	static ServerConfig serverConfig;
	return (serverConfig);
}
