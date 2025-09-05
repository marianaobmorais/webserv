#include <iostream>
#include <exception>
#include <cstdlib>
#include <request/RequestParse.hpp>
#include <request/RequestParseError.hpp>

void RequestParse::handleRawRequest(const std::string& rawRequest, HttpRequest& request)
{
	std::string buffer;
	int line = 0;

	for (std::size_t i = 0; i < rawRequest.size(); ++i)
	{
		try
		{
			if (rawRequest.at(i) == '\r' && rawRequest.at(i + 1) == '\n') //line-request or headers
			{
				i+=2;
				if (rawRequest.at(i) == '\r' && rawRequest.at(i + 1) == '\n') //end or body
					;
				else if (line++ == 0) // request line
				{
					requestLine(buffer, request);
					buffer.clear();
				}
				else //header
				{
					;//headers();
				}
			}
			buffer.push_back(rawRequest.at(i));
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << buffer << std::endl;
	request.getHttpVersion();
}

std::vector<std::string>	RequestParse::split(const std::string& str, const std::string& sep)
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

void	RequestParse::requestLine(const std::string& buffer, HttpRequest& request)
{
	const std::vector<std::string> tokens = split(buffer, " ");

	std::cout << " -- requestline -- " << std::endl;

	if (tokens.size() != 3)
		request.setParseError(RequestParseError::BadRequestLine);
	else
	{
		method(tokens[0], request);
		request.setUri(tokens[1]);

		//TODO who controls the version?
		std::vector<std::string> httpVersion = split(tokens[2].substr(5), ".");

		request.setMajor(std::atoi(httpVersion[0].c_str()));
		request.setMinor(std::atoi(httpVersion[1].c_str()));
	}
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

// void RequestParse::headers(const std::string& method, HttpRequest& request)
// {

// }

//HttpRequest::setUri(requestLine[1]); //after header host