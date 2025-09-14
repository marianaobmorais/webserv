#include <sstream>
#include <response/ResponseBuilder.hpp>
#include <utils/Logger.hpp>

const std::string	ResponseBuilder::responseToString(HttpResponse& response)
{
	std::ostringstream oss;

	Logger::instance().log(DEBUG, "responseToString");

	oss << "HTTP/" << response.getHttpVersion() << " "
		<< response.getStatusCode() << " "
		<< response.getReasonPhrase() << "\r\n";

	oss << "Server: Webservinho/1.0" << "\r\n";
	oss << "Date:"; // << timestamp << "\r\n";
	//TODO connection

	std::map<std::string, std::string>& headers = response.getHeaders();
	std::map<std::string, std::string>::const_iterator it;
	for (it = headers.begin(); it != headers.end(); ++it)
	{
		oss << it->first << ":" << it->second << "\r\n";
	}

	//TODO body
}

//TODO static page

//TODO cgi

//TODO error