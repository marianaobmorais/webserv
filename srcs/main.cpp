#include "../includes/HttpRequest.hpp"

int	main(void)
{
	std::string	clientRequest = "GET /hello HTTP/1.1\r\n Host: localhost:8000\r\n User-Agent: curl/7.68.0\r\n Accept: */*\r\n \r\n";

	HttpRequest request(clientRequest);

	return (0);
}