#include <sstream>
#include <response/ResponseBuilder.hpp>
#include <utils/Logger.hpp>

const std::string	ResponseBuilder::fmtTimestamp(void)
{
	std::string timestamp;
	std::time_t now = std::time(0);
	tm* timeinfo = std::gmtime(&now);
	char buf[100];
	std::strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	timestamp += buf;
	return (timestamp);
}

void	ResponseBuilder::setMinimumHeaders(HttpResponse& response)
{
	response.addHeader("Date", fmtTimestamp());
	response.addHeader("Server", "Webservinho/1.0");
}

std::string	ResponseBuilder::errorPageGenerator(ResponseStatus::code code)
{
	std::ostringstream oss;

	oss << "<!DOCTYPE html>\r\n"
		<< "<html>\r\n"
		<< "<head><title>Erro " << code << "</title></head>\r\n"
		<< "<body style=\"text-align: center; padding: 50px;\">\r\n"
		<< "<h1>" << code << " - Erro</h1>\r\n"
		<< "<img src=\"https://http.cat/" << code
		<< " alt=\"Erro HTTP " << code << "\" style=\"max-width: 80%; height: auto;\">\r\n"
		<< "</body>\r\n"
		<< "</html>\r\n";

	return (oss.str());
}

const std::string	ResponseBuilder::responseToString(HttpResponse& response)
{
	std::ostringstream oss;

	Logger::instance().log(DEBUG, "[Started] ResponseBuilder::responseToString");

	setMinimumHeaders(response);// remove

	//response line
	oss << "HTTP/" << response.getHttpVersion() << " "
		<< response.getStatusCode() << " "
		<< response.getReasonPhrase() << "\r\n";

	//TODO connection

	//headers
	const std::map<std::string, std::string>& headers = response.getHeaders();
	std::map<std::string, std::string>::const_iterator it;
	for (it = headers.begin(); it != headers.end(); ++it)
	{
		oss << it->first << ":" << it->second << "\r\n";
	}

	if (!response.isChunked())
		oss << response.getBody();
	//else
		//TODO body chunks

	Logger::instance().log(DEBUG, "[Finished] ResponseBuilder::responseToString");
	return (oss.str());
}

void	ResponseBuilder::run(HttpResponse& response /* request */ /* config */)
{
	Logger::instance().log(DEBUG, "[Started] ResponseBuilder::run");

	setMinimumHeaders(response);

	if (response.getStatusCode() >= 400)
	{
		//TODO close connection ?
		//TODO clear body ?
		std::string content;
		if (false) //find error in config
		{
			const std::string& path = "path"; //config

			//if readfile(path, content)
			{
				response.setChunked(false);
				//response.addHeader("Content-Type", mimeType(path));
				//response.addHeader("Content-Length", to_string(content.size()));
				response.appendBody(content);
			}
		}
		else
		{
			content = errorPageGenerator(response.getStatusCode());
			response.setChunked(false);
			response.addHeader("Content-Type", "text/html");
			//response.addHeader("Content-Length", to_string(content.size()));
			response.appendBody(content);
		}
	}

	//body cgi static page

	Logger::instance().log(DEBUG, "[Finished] ResponseBuilder::run");
}
