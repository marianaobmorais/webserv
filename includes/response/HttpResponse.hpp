#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <map>

//webserv
#include <response/ResponseStatus.hpp>

//Data Transfer Object
class HttpResponse
{
	private:
		ResponseStatus::code				_statusCode;
		const std::string&					_reasonPhrase;
		const std::string&					_version;
		std::map<std::string, std::string>	_headers;
		std::string							_body;
		bool								_chunked; // transfer encoding

		HttpResponse& operator=(const HttpResponse& rhs);
		HttpResponse(const HttpResponse& rhs);

	public:
		HttpResponse();
		~HttpResponse();

		//setters
		void	setStatusCode(const ResponseStatus::code& code);
		void	appendBody(const std::string& body);
		void	appendBody(char c);
		void	addHeader(const std::string& name, const std::string& value);
		void	setChunked(bool chunked);

		//getters
		ResponseStatus::code		getStatusCode(void) const;
		const std::string&			getHttpVersion(void) const;
		const std::string&			getBody(void) const;
		const std::string&			getHeader(const std::string& name) const;
		bool						isChunked(void) const;
};

#endif //HTTP_RESPONSE_HPP