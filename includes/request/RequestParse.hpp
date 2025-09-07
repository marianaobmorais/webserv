#ifndef REQUEST_PARSE_HPP
#define REQUEST_PARSE_HPP

//webserv
#include <request/RequestMethod.hpp>
#include <request/HttpRequest.hpp>

class RequestParse
{
	private:
		RequestParse(); //blocked
		~RequestParse(); //blocked
		RequestParse(const RequestParse& rhs); //blocked
		RequestParse& operator=(const RequestParse& rhs); //blocked

		static void	requestLine(const std::string& str, HttpRequest& request);
		static void	method(const std::string& method, HttpRequest& request);
		static void	headers(const std::string& header, HttpRequest& request);
		static void	body(char c, HttpRequest& request);

	public:
		static void	handleRawRequest(const std::string& rawRequest, HttpRequest& request);
};

#endif //REQUEST_PARSE_HPP