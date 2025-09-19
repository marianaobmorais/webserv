#include <init/ServerConfig.hpp>

ServerConfig::ServerConfig() : root("www/app"), index("index.html"), cgiPath("al") {}

ServerConfig::~ServerConfig() {}

ServerConfig&	ServerConfig::instance()
{
	static ServerConfig serverConfig;
	return (serverConfig);
}
