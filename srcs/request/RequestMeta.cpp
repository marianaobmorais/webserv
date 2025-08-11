#include <RequestMeta.hpp>

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

int	RequestMeta::getContentLength(void) { return (this->_contentLength); }

bool	RequestMeta::getChunked(void) { return (this->_chunked); }

bool	RequestMeta::getConnectionClose(void) { return (this->_connectionClose); }

bool	RequestMeta::getExpectContinue(void) { return (this->_expectContinue); }

std::string	RequestMeta::getHost(void) { return (this->_host); }