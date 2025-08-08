#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>

struct HttpMethod
{
	enum Method
	{
		GET = 0, POST, DELETE, PUT, INVALID
	};
};

class HttpRequest
{
	private:

		std::map<std::string, std::string>	_headers;
		HttpMethod::Method					_method;
		std::string							_uri;
		int									_major;
		int									_minor;

		//setters
		void	setHeaders(std::map<std::string, std::string> headers);
		void	setMethod(const std::string& method);
		void	setUri(std::string uri);
		void	setMajor(int major);
		void	setMinor(int minor);

		//parser
		std::vector<std::string>	split(const std::string& str, const std::string& sep);
		void						saveRequestLine(const std::string& str);

	public:

		HttpRequest(const std::string& request);
		~HttpRequest();
		//add copy assignment?
		//add copy?

		//getters
		const std::map<std::string, std::string>&	getHeaders(void) const;
		HttpMethod::Method							getMethod(void) const; //convert string?
		const std::string&							getUri(void) const;
		int											getMajor(void) const;
		int											getMinor(void) const;
};

#endif //HTTP_REQUEST_HPP