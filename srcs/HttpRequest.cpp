#include "HttpRequest.hpp"

HttpRequest::HttpRequest(const std::string& request) {}

HttpRequest::~HttpRequest() {}

void	HttpRequest::setHeaders(std::map<std::string, std::string> headers)
{
	this->_headers = headers;
}

void	HttpRequest::setMethod(HttpMethod::Method method)
{
	this->_method = method;
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

int	HttpRequest::getMajor(int major) const { return (this->_major); }

int	HttpRequest::getMinor(int minor) const { return (this->_minor); }