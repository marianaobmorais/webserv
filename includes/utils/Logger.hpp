#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

enum LogLevel
{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

class Logger
{
	private:
		std::ofstream	_logFile;

		const std::string	levelToString(LogLevel level) const;

	public:
		Logger(const std::string& filename);
		~Logger();

		void	log(LogLevel level, const std::string& message);
};

#endif //LOGGER_HPP