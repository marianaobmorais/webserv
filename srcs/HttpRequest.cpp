#include <HttpRequest.hpp>

HttpRequest::HttpRequest(const std::string& request) {}

HttpRequest::~HttpRequest() {}

void	HttpRequest::setMethod(const HttpMethod::Method& method)
{
	this->_method = method;
}

void	HttpRequest::setUri(const std::string& uri) { this->_uri = uri; }

void	HttpRequest::setMajor(int major) { this->_major = major; }

void	HttpRequest::setMinor(int minor) { this->_minor = minor; }

void	HttpRequest::setHeaders(const RequestHeader& headers)
{
	this->_headers = headers;
}

void	HttpRequest::setMeta(const RequestMeta& meta)
{
	this->_meta = meta;
}

void	HttpRequest::setBodyRef(const std::string& body_ref)
{
	this->_bodyRef = body_ref;
}

void	HttpRequest::setParseError(RequestParseError::reason reason)
{
	this->_parseError = reason;
}

HttpMethod::Method	HttpRequest::getMethod(void) const
{
	return (this->_method);
}

const std::string&	HttpRequest::getUri(void) const { return (this->_uri); }

int*	HttpRequest::getHttpVersion(void) const
{
	int version[2] = {this->_major, this->_minor};

	return (version);
}

const RequestHeader&	HttpRequest::getHeaders(void) const
{
	return (this->_headers);
}

const RequestMeta&	HttpRequest::getMeta(void) const
{
	return (this->_meta);
}

const std::string&	HttpRequest::getBodyRef(void) const
{
	return (this->_bodyRef);
}

RequestParseError::reason	HttpRequest::getParseError(void) const
{
	return (this->_parseError);
}
