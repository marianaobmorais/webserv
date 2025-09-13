#include "response/HttpResponse.hpp"

HttpResponse::HttpResponse()
{
	setStatusCode(ResponseStatus::OK);
	setChunked(false);
}

HttpResponse::~HttpResponse() {}

void	HttpResponse::setStatusCode(const ResponseStatus::code& code)
{
	this->_statusCode = code;
}

void	HttpResponse::appendBody(const std::string& body)
{
	this->_body += body;
}

void	HttpResponse::appendBody(char c)
{
	this->_body.push_back(c);
}

void	HttpResponse::addHeader(const std::string& name, const std::string& value)
{
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

void	HttpResponse::setChunked(bool chunked)
{
	this->_chunked = chunked;
}

ResponseStatus::code	HttpResponse::getStatusCode() const
{
	return (this->_statusCode);
}

const std::string&	HttpResponse::getHttpVersion(void) const
{
		return (this->_version);
}

const std::string& HttpResponse::getHeader(const std::string& name) const
{
	std::map<std::string, std::string>::const_iterator c_it;

	c_it = this->_headers.find(name);
	if (c_it != this->_headers.end())
		return (c_it->second);
	return (name);
}

const std::string&	HttpResponse::getBody(void) const
{
	return (this->_body);
}

bool	HttpResponse::isChunked(void) const { return (this->_chunked); }
