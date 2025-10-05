#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP

#include <string>
#include <vector>

class LocationConfig
{
	private:
		std::string					_path;
		// std::string					_root; //A location block root can override ServerRoot for a specific path
		// bool						_autoIndex;
		// std::vector<std::string>	_methods; //can override server-level defaults
	public:
		//accessors
};

#endif //LOCATIONCONFIG_HPP