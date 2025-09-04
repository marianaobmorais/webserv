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

	public:
		static const HttpRequest& handleRawRequest(const std::string& rawRequest);
};

#endif //REQUEST_PARSE_HPP