#include "request/RequestMeta.hpp"

RequestMeta::RequestMeta() {}

RequestMeta::~RequestMeta() {}

void	RequestMeta::setContentLength(int content_length)
{
	this->_contentLength = content_length;
}

void	RequestMeta::setChunked(bool chunked)
{
	this->_chunked = chunked;
}

void	RequestMeta::setConnectionClose(bool connection_close)
{
	this->_connectionClose = connection_close;
}

void	RequestMeta::setExpectContinue(bool expect_continue)
{
	this->_expectContinue = expect_continue;
}

void	RequestMeta::setHost(const std::string& host)
{
	this->_host = host;
}

int	RequestMeta::getContentLength(void) const { return (this->_contentLength); }

bool	RequestMeta::isChunked(void) const { return (this->_chunked); }

bool	RequestMeta::shouldClose(void) const { return (this->_connectionClose); }

bool	RequestMeta::getExpectContinue(void) const { return (this->_expectContinue); }

std::string	RequestMeta::getHost(void) const { return (this->_host); }