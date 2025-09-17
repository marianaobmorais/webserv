#include <sstream>
#include <response/ResponseBuilder.hpp>
#include <utils/Logger.hpp>
#include <utils/string_utils.hpp>

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

void	ResponseBuilder::handleStaticPage(HttpResponse& response,
			const std::string& output, const std::string& mimeType)
{
	response.setChunked(false);
	response.addHeader("Content-Type", mimeType);
	response.addHeader("Content-Length", toString(output.size()));
	response.appendBody(output);
}

void	ResponseBuilder::handleCgiOutput(HttpResponse& response, const std::string& output)
{
	std::size_t sep = output.find("\r\n\r\n");
	if (sep == std::string::npos)
	{
		response.setStatusCode(ResponseStatus::BadGateway);
		return ;
	}

	std::string headersPart = output.substr(0, sep);
	std::string bodyPart = output.substr(sep + 4);

	std::istringstream headerStream(headersPart);
	std::string line;

	while (std::getline(headerStream, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line = line.substr(0, line.size() - 1);

		std::size_t colon = line.find(":");
		if (colon != std::string::npos)
		{
			std::string key = trim(line.substr(0, colon));
			std::string value = trim(line.substr(colon + 1));
			response.addHeader(key, value);

			if (toLower(key) == "status")
			{
				std::istringstream iss(value);
				int status;
				if (iss >> status)
					response.setStatusCode(static_cast<ResponseStatus::code>(status));
			}
		}
	}

	response.appendBody(bodyPart);
	response.addHeader("Content-Length", toString(bodyPart.size()));
}

void	ResponseBuilder::run(HttpResponse& response, const std::string& output /* request */ /* config */)
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

			// if readfile(path, content)
			// {
			// 	staticPage(response, content, mimeType(path));
			// }
		}
		else
		{
			content = errorPageGenerator(response.getStatusCode());
			handleStaticPage(response, content, "text/html");
		}
	}

	// if (StaticPage)
	handleStaticPage(response, output, "text/html" /* mimeType(path) */);
	// if (CGI)
	// 	handleCgiOutput(response, output);

	Logger::instance().log(DEBUG, "[Finished] ResponseBuilder::run");
}
