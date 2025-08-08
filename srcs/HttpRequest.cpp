#include "../includes/HttpRequest.hpp"

HttpRequest::HttpRequest(const std::string& request)
{
	std::vector<std::string> lines = HttpRequest::split(request, "\r\n");
	HttpRequest::saveRequestLine(lines[0]);

	// for (size_t i = 0; i < lines.size(); ++i)
	// {
	// 	std::cout << lines[i] << std::endl;
	// }
}

HttpRequest::~HttpRequest() {}

std::vector<std::string>	HttpRequest::split(const std::string& str, const std::string& sep)
{
	std::vector<std::string>	tokens;
	size_t						start = 0;
	size_t						end = str.find(sep);

	while (end != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + sep.length();
		end = str.find(sep, start);
	}
	tokens.push_back(str.substr(start));
	return (tokens);
}

void	HttpRequest::saveRequestLine(const std::string& str)
{
	std::vector<std::string> requestLine = HttpRequest::split(str, " ");

	HttpRequest::setMethod(requestLine[0]);
	HttpRequest::setUri(requestLine[1]);

	std::vector<std::string> httpVersion = HttpRequest::split(requestLine[2].substr(5), ".");

	HttpRequest::setMajor(std::atoi(httpVersion[0].c_str()));
	HttpRequest::setMinor(std::atoi(httpVersion[1].c_str()));
}

void	HttpRequest::setHeaders(std::map<std::string, std::string> headers)
{
	this->_headers = headers;
}

void	HttpRequest::setMethod(const std::string& method)
{
	if (method == "GET")
		this->_method = HttpMethod::GET;
	else if (method == "POST")
		this->_method = HttpMethod::POST;
	else if (method == "DELETE")
		this->_method = HttpMethod::DELETE;
	else if (method == "PUT")
		this->_method = HttpMethod::PUT;
	else
		this->_method = HttpMethod::INVALID;
}

void	HttpRequest::setUri(std::string uri)
{
	this->_uri = uri;
}

void	HttpRequest::setMajor(int major) { this->_major = major; }

void	HttpRequest::setMinor(int minor) { this->_minor = minor; }

const std::map<std::string, std::string>&	HttpRequest::getHeaders(void) const
{
	return (this->_headers);
}

HttpMethod::Method	HttpRequest::getMethod(void) const
{
	return (this->_method);
}

const std::string&	HttpRequest::getUri(void) const
{
	return (this->_uri);
}

int	HttpRequest::getMajor(void) const { return (this->_major); }

int	HttpRequest::getMinor(void) const { return (this->_minor); }