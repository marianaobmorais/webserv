#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>
#include <vector>

//webserv
#include <request/RequestMethod.hpp>
#include <request/RequestMeta.hpp>
#include <request/RequestParseError.hpp>
#include <request/RequestState.hpp>

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
		std::string							_body;
		RequestParseError::reason			_parseError;
		RequestState::state					_state;
		std::string							_rawRequest;
		std::string							_buffer;

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
		void	appendBody(const std::string& body);
		void	appendBody(char c);
		void	setParseError(RequestParseError::reason reason);
		void	addHeader(const std::string& name, const std::string& value);
		void	setRequestState(RequestState::state state);
		void	appendRaw(const std::string& chunk);
		void	clearBuffer(void);

		//getters
		RequestMethod::Method		getMethod(void) const;
		const std::string&			getUri(void) const;
		const std::vector<int>		getHttpVersion(void) const;
		const RequestMeta&			getMeta(void) const;
		RequestMeta&				getMeta(void);
		const std::string&			getBody(void) const;
		RequestParseError::reason	getParseError(void) const;
		const std::string&			getHeader(const std::string& name) const;
		RequestState::state			getState(void) const;
		std::string&				getRaw(void);
		std::string&				getBuffer(void);
};

#endif //HTTP_REQUEST_HPP