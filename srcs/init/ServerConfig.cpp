#include <init/ServerConfig.hpp>

ServerConfig::ServerConfig() : root("/home/jose/webserv_42/webservinho_app"),
	index("index.html"),
	cgiPath("/home/jose/webserv_42/webservinho_app/cgi-bin"),
	error_page_404("errors/404.html"),
	autoindex(true),
	upload_path("/home/jose/webserv_42/webservinho_app/uploads")
{}

ServerConfig::~ServerConfig() {}

ServerConfig&	ServerConfig::instance()
{
	static ServerConfig serverConfig;
	return (serverConfig);
}
