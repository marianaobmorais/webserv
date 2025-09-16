#include "../includes/WebServer.hpp"
#include "../includes/ServerSocket.hpp"
#include "../includes/Config.hpp"
#include <iostream>
#include <string>

int	main(int argc, char** argv)
{
	std::string	configFile;

	if (argc > 2)
	{
		std::cout << "usage: ./webserv [config_file]" << std::endl;
		return (1);
	}
	if (argc == 1)
		configFile = "defaut.config"; //create file and put it in the repository?
	if (argc == 2)
		configFile = argv[1];
	try
	{
		Config		config(configFile);
		//config.parseConfig();

		WebServer	server(config);
		server.startServer();
		server.runServer();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}