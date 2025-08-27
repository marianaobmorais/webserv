#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include <vector>

//webserv
#include "request/RequestMethod.hpp"
#include "request/RequestMeta.hpp"
#include "request/RequestParseError.hpp"

//Data Transfer Object
class HttpRequest
{
	private:
		RequestMethod::Method				_method;
		std::string							_uri;
		int									_major;
		int									_minor;
		std::map<std::string, std::string>	_headers;
		RequestMeta							_meta;
		std::string							_bodyRef; //TODO
		RequestParseError::reason			_parseError;

	public:
		HttpRequest();
		~HttpRequest();
		HttpRequest& operator=(const HttpRequest& rhs); //TODO
		HttpRequest(const HttpRequest& rhs); //TODO

		//setters
		void	setMethod(const RequestMethod::Method& method);
		void	setUri(const std::string& uri);
		void	setMajor(int major);
		void	setMinor(int minor);
		void	setBodyRef(const std::string& body_ref);
		void	setParseError(RequestParseError::reason reason);
		void	addHeader(const std::string& name, const std::string& value);

		//getters
		RequestMethod::Method		getMethod(void) const;
		const std::string&			getUri(void) const;
		const std::vector<int>		getHttpVersion(void) const;
		const RequestMeta&			getMeta(void) const;
		RequestMeta&				getMeta(void);
		const std::string&			getBodyRef(void) const; //TODO
		RequestParseError::reason	getParseError(void) const;
		const std::string&			getHeader(const std::string& name) const;
};

#endif //HTTP_REQUEST_HPP