#include <request/HttpRequest.hpp>
#include <request/RequestParse.hpp>
#include <iostream>

int	main(void)
{
	std::string	clientRequest = "GET /hello HTTP/1.1\r\nHost: localhost:8000\r\nUser-Agent: curl/7.68.0\r\nAccept: */*\r\n\r\n";

	return (0);
}
