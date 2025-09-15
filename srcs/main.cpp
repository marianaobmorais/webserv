#include <request/HttpRequest.hpp>
#include <request/RequestParse.hpp>
#include <response/HttpResponse.hpp>
#include <response/ResponseBuilder.hpp>
#include <utils/Logger.hpp>
#include <iostream>

int	main(void)
{
	Logger::instance();

	// std::string clientRequest =
	// 	"POST /api/login HTTP/1.1\r\n"
	// 	"Host: localhost:8000\r\n"
	// 	"Content-Type: application/json\r\n"
	// 	"Content-Length: 49\r\n"
	// 	"Connection: close\r\n"
	// 	"\r\n"
	// 	"{\r\n"
	// 	"  \"username\": \"alice\",\r\n"
	// 	"  \"password\": \"12345\"\r\n"
	// 	"}\r\n";

	// HttpRequest request;

	// for (std::size_t i = 0; i < clientRequest.size(); ++i)
	// {
	// 	std::string chunk = clientRequest.substr(i, 1); // 1 byte por vez
	// 	RequestParse::handleRawRequest(chunk, request);
	// }

	// if (request.getParseError() != RequestParseError::OK)
	// 	std::cout << "Error: " << request.getParseError() << std::endl;
	// else
	// {
	// 	std::cout << "Method: " << request.getMethod() << std::endl;
	// 	std::cout << "URI: " << request.getUri() << std::endl;
	// 	std::cout << "HttpVersion: " << request.getHttpVersion()[0] << request.getHttpVersion()[1] << std::endl;
	// 	std::cout << " -- HttpRequest Meta -- " << std::endl;
	// 	std::cout << "Host: " << request.getMeta().getHost() << std::endl;
	// 	std::cout << "Content-Length: " << request.getMeta().getContentLength() << std::endl;
	// 	std::cout << "Tranfer-Encoding: " << request.getMeta().isChunked() << std::endl;
	// 	std::cout << "Connection close: " << request.getMeta().shouldClose() << std::endl;
	// 	std::cout << "Expect: " << request.getMeta().getExpectContinue() << std::endl;
	// 	std::cout << "Body: " << request.getBody() << std::endl;
	// }

	HttpResponse response;

	response.setStatusCode(ResponseStatus::NotFound);

	ResponseBuilder::run(response);

	std::cout << ResponseBuilder::responseToString(response);

	return (0);
}
