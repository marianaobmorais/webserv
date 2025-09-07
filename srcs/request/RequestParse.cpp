#include <iostream>
#include <exception>
#include <cstdlib>
#include <request/RequestParse.hpp>
#include <request/RequestParseError.hpp>
#include <request/RequestState.hpp>
#include <string_utils.hpp>

void	RequestParse::handleRawRequest(const std::string& chunk, HttpRequest& request)
{
	request.appendRaw(chunk);
	std::string& rawRequest = request.getRaw();

	std::string buffer;
	std::size_t i = 0;

	while (i < rawRequest.size())
	{
		if (i + 1 < rawRequest.size() && rawRequest[i] == '\r' && rawRequest[i + 1] == '\n')
		{
			if (request.getState() == RequestState::RequestLine)
			{
				requestLine(buffer, request);
				request.setRequestState(RequestState::Headers);
			}
			else if (request.getState() == RequestState::Headers)
			{
				if (buffer.empty())
					request.setRequestState(RequestState::Body);
				else
				{
					headers(buffer, request);
				}
			}
			buffer.clear();
			i += 2;
			continue ;
		}
		if (request.getState() < RequestState::Body)
		{
			buffer.push_back(rawRequest[i]);
			++i;
		}
		else
		{
			body(rawRequest[i], request);
			++i;
		}
	}
	request.getRaw().erase(0, i);
}

void	RequestParse::requestLine(const std::string& buffer, HttpRequest& request)
{
	const std::vector<std::string> tokens = split(buffer, " ");

	if (tokens.size() != 3)
	{
		request.setParseError(RequestParseError::BadRequestLine);
		return ;
	}

	method(tokens[0], request);
	request.setUri(tokens[1]);

	const std::string version = tokens[2];
	if (version.size() < 8 || version.substr(0, 5) != "HTTP/"
		|| version.find('.') == std::string::npos)
	{
		request.setParseError(RequestParseError::InvalidVersion);
		return ;
	}

	std::vector<std::string> parts = split(version.substr(5), ".");
	if (parts.size() != 2)
	{
		request.setParseError(RequestParseError::InvalidVersion);
		return ;
	}
	//TODO who controls the version?
	if (parts[0] != "1" || parts[1] != "1")
	{
		request.setParseError(RequestParseError::UnsupportedVersion);
		return ;
	}

	request.setMajor(std::atoi(parts[0].c_str()));
	request.setMinor(std::atoi(parts[1].c_str()));
}

void	RequestParse::method(const std::string& method, HttpRequest& request)
{
	if (method == "GET")
		request.setMethod(RequestMethod::GET);
	else if (method == "POST")
		request.setMethod(RequestMethod::POST);
	else if (method == "DELETE")
		request.setMethod(RequestMethod::DELETE);
	else if (method == "PUT")
		request.setMethod(RequestMethod::PUT);
	else
	{
		request.setMethod(RequestMethod::INVALID);
		request.setParseError(RequestParseError::InvalidMethod);
	}
}

void	RequestParse::headers(const std::string& buffer, HttpRequest& request)
{
	std::string::size_type pos = buffer.find(":");

	if (pos == std::string::npos)
	{
		request.setParseError(RequestParseError::InvalidHeader);
		return ;
	}

	std::string key = toLower(trim(buffer.substr(0, pos)));
	std::string value = trim((pos + 1 < buffer.size()
							? buffer.substr(pos + 1) : std::string()));

	if (key == "host")
	{
		request.setUri(value + request.getUri()); //TODO 
		request.getMeta().setHost(value);
	}
	else if (key == "content-length")
		request.getMeta().setContentLength(std::atoi(value.c_str()));
	else if (key == "transfer-encoding")
		request.getMeta().setChunked(true);
	else if (key == "connection")
		request.getMeta().setConnectionClose(toLower(value) == "close");
	else if (key == "expect")
	{
		if (toLower(value) == "100-continue")
			request.getMeta().setExpectContinue(true);
		else
			request.setParseError(RequestParseError::InvalidHeader);
	}
	request.addHeader(key, value);
}

void	RequestParse::body(char c, HttpRequest& request)
{
	if (!request.getMeta().isChunked())
	{
		request.appendBody(c);
		if ((int) request.getBody().size() >= request.getMeta().getContentLength())
			request.setRequestState(RequestState::Complete);

	}
}