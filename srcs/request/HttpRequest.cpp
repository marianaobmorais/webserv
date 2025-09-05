#include "request/HttpRequest.hpp"

HttpRequest::HttpRequest()
{
	setMethod(RequestMethod::INVALID);
	setParseError(RequestParseError::OK);
	getMeta().setContentLength(-1);
	getMeta().setChunked(false);
	getMeta().setConnectionClose(true);
	getMeta().setExpectContinue(false);
}

HttpRequest::~HttpRequest() {}

void	HttpRequest::setMethod(const RequestMethod::Method& method)
{
	this->_method = method;
}

void	HttpRequest::setUri(const std::string& uri) { this->_uri = uri; }

void	HttpRequest::setMajor(int major) { this->_major = major; }

void	HttpRequest::setMinor(int minor) { this->_minor = minor; }

void	HttpRequest::addHeader(const std::string& name, const std::string& value)
{
	//apply lowercase
	//refactor insertion
	std::map<std::string, std::string>::iterator it;
	it = this->_headers.find(name);
	if (it != _headers.end())
	{
		std::string current = it->second;
		std::string new_ = current + "," + value;
		_headers.erase(it);
		_headers[name] = new_;
	}
	else
		_headers[name] = value;
}

void	HttpRequest::setBodyRef(const std::string& body_ref)
{
	this->_bodyRef = body_ref;
}

void	HttpRequest::setParseError(RequestParseError::reason reason)
{
	this->_parseError = reason;
}

RequestMethod::Method	HttpRequest::getMethod(void) const
{
	return (this->_method);
}

const std::string&	HttpRequest::getUri(void) const { return (this->_uri); }

const std::vector<int>	HttpRequest::getHttpVersion(void) const
{
	int version[2] = {this->_major, this->_minor};

	return (std::vector<int>(version, version + 2));
}

const std::string& HttpRequest::getHeader(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator c_it;

	c_it = this->_headers.find(name);
	if (c_it != this->_headers.end())
		return (c_it->second);
	return (name);
}

const RequestMeta&	HttpRequest::getMeta(void) const
{
	return (this->_meta);
}

RequestMeta&	HttpRequest::getMeta(void)
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
