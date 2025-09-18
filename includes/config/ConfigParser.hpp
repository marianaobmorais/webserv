#ifndef CONFIGPARSER_H
# define CONFIGPARSER_H

#include <Config.hpp>
#include <string>

class ConfigParser
{
	private:
		ConfigParser(std::string file);
		ConfigParser(ConfigParser const& src);
		ConfigParser&		operator=(ConfigParser const& rhs);
		~ConfigParser(void);
	public:
		static Config		parseFile(std::string const& configFile); //populates the Config::_servers vector
};

#endif //CONFIGPARSER_H