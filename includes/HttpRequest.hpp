#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>

//webserv
#include <HttpMethod.hpp>
#include <RequestHeader.hpp>
#include <RequestMeta.hpp>
#include <RequestParseError.hpp>

//Data Transfer Object
class HttpRequest
{
	private:
		HttpMethod::Method			_method;
		std::string					_uri;
		int							_major;
		int							_minor;
		RequestHeader				_headers;
		RequestMeta					_meta;
		std::string					_bodyRef;
		RequestParseError::reason	_parseError;

		//setters
		void	setMethod(const HttpMethod::Method& method);
		void	setUri(const std::string& uri);
		void	setMajor(int major);
		void	setMinor(int minor);
		void	setHeaders(const RequestHeader& headers);
		void	setMeta(const RequestMeta& meta);
		void	setBodyRef(const std::string& body_ref);
		void	setParseError(RequestParseError::reason reason);

	public:
		HttpRequest(const std::string& request);
		~HttpRequest();

		//getters
		HttpMethod::Method			getMethod(void) const;
		const std::string&			getUri(void) const;
		int*						getHttpVersion(void) const;
		const RequestHeader&		getHeaders(void) const;
		const RequestMeta&			getMeta(void) const;
		const std::string&			getBodyRef(void) const;
		RequestParseError::reason	getParseError(void) const;
};

#endif //HTTP_REQUEST_HPP