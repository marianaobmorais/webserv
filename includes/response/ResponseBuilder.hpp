#ifndef RESPONSE_BUILDER_HPP
#define RESPONSE_BUILDER_HPP

//webserv
#include <response/HttpResponse.hpp>

class ResponseBuilder
{
	private:
		ResponseBuilder(); //blocked
		~ResponseBuilder(); //blocked
		ResponseBuilder(const ResponseBuilder& rhs); //blocked
		ResponseBuilder& operator=(const ResponseBuilder& rhs); //blocked

	public:
		static const std::string	responseToString(HttpResponse& response);
};

#endif //RESPONSE_BUILDER_HPP