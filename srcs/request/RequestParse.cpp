#include <RequestParse.hpp>

// 	std::vector<std::string> lines = HttpRequest::split(request, "\r\n");

// 	//start-line
// 	HttpRequest::saveRequestLine(lines[0]);

// 	for (size_t i = 1; i < lines.size(); ++i)
// 	{
// 		std::cout << lines[i] << std::endl;
// 	}

// std::vector<std::string>	HttpRequest::split(const std::string& str, const std::string& sep)
// {
// 	std::vector<std::string>	tokens;
// 	size_t						start = 0;
// 	size_t						end = str.find(sep);

// 	while (end != std::string::npos)
// 	{
// 		tokens.push_back(str.substr(start, end - start));
// 		start = end + sep.length();
// 		end = str.find(sep, start);
// 	}
// 	tokens.push_back(str.substr(start));
// 	return (tokens);
// }

// void	HttpRequest::saveRequestLine(const std::string& str)
// {
// 	std::vector<std::string> requestLine = HttpRequest::split(str, " ");

// 	HttpRequest::setMethod(requestLine[0]);
// 	HttpRequest::setUri(requestLine[1]);

// 	std::vector<std::string> httpVersion = HttpRequest::split(requestLine[2].substr(5), ".");

// 	HttpRequest::setMajor(std::atoi(httpVersion[0].c_str()));
// 	HttpRequest::setMinor(std::atoi(httpVersion[1].c_str()));
// }

// void	HttpRequest::setMethod(const std::string& method)
// {
// 	if (method == "GET")
// 		this->_method = RequestMethod::GET;
// 	else if (method == "POST")
// 		this->_method = RequestMethod::POST;
// 	else if (method == "DELETE")
// 		this->_method = RequestMethod::DELETE;
// 	else if (method == "PUT")
// 		this->_method = RequestMethod::PUT;
// 	else
// 		this->_method = RequestMethod::INVALID;
// }