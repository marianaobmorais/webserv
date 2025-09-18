#ifndef RESPONSE_BUILDER_HPP
#define RESPONSE_BUILDER_HPP

//webserv
#include <response/HttpResponse.hpp>
#include <response/ResponseStatus.hpp>

class ResponseBuilder
{
	private:
		ResponseBuilder(); //blocked
		~ResponseBuilder(); //blocked
		ResponseBuilder(const ResponseBuilder& rhs); //blocked
		ResponseBuilder& operator=(const ResponseBuilder& rhs); //blocked

		static const std::string	fmtTimestamp(void);
		static void					setMinimumHeaders(HttpResponse& response);
		static std::string			errorPageGenerator(ResponseStatus::code code);
		static void					handleStaticPage(HttpResponse& response,
										const std::string& output,
										const std::string& mimeType);
		static void					handleCgiOutput(HttpResponse& response, const std::string& output);

	public:
		static const std::string	responseToString(HttpResponse& response);
		static void					run(HttpResponse& response, const std::string& output /* config */);
};

#endif //RESPONSE_BUILDER_HPP