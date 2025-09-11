#include <utils/Logger.hpp>

Logger::Logger()
{
	std::time_t now = time(0);
	tm* timeinfo = localtime(&now);
	char timestamp[20];
	std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d", timeinfo);

	std::string	filename = "./logs/webserv_";
	filename += timestamp;
	filename += ".log";

	_logFile.open(filename.c_str(), std::ios::app);
	if (!_logFile.is_open())
	{
		std::cerr << "Error opening log file." << std::endl;
	}
}

Logger::~Logger() { _logFile.close(); }

Logger&	Logger::instance()
{
	static Logger logger;
	return (logger);
}

void	Logger::log(LogLevel level, const std::string& message)
{
	std::time_t now = time(0);
	tm* timeinfo = localtime(&now);
	char timestamp[20];
	std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

	std::ostringstream logEntry;

	logEntry << "[" << timestamp << "] "
				<< levelToString(level) << ": " << message
				<< std::endl;

	if (DEV == 0 && level >= INFO)
		std::cout << logEntry.str();
	else if (DEV == 1)
		std::cout << logEntry.str();

	if (_logFile.is_open())
	{
		_logFile << logEntry.str();
		_logFile.flush();
	}
}

const std::string	Logger::levelToString(LogLevel level) const
{
	switch (level)
	{
		case DEBUG:
			return "DEBUG";
		case INFO:
			return "INFO";
		case WARNING:
			return "WARNING";
		case ERROR:
			return "ERROR";
		case CRITICAL:
			return "CRITICAL";
		default:
			return "UNKNOWN";
	}
}
