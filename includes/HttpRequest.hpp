#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <map>

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
		void	setMethod(HttpMethod::Method method);
		void	setUri(std::string uri);
		void	setMajor(int major);
		void	setMinor(int minor);

	public:

		HttpRequest(const std::string& request);
		~HttpRequest();
		//add copy assignment?
		//add copy?

		//parser

		//getters
		const std::map<std::string, std::string>&	getHeaders(void) const;
		HttpMethod::Method							getMethod(void) const; //convert string?
		const std::string&							getUri(void) const;
		int											getMajor(int major) const;
		int											getMinor(int minor) const;
};

#endif //HTTP_REQUEST_HPP