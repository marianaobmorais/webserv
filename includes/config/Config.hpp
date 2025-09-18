#ifndef CONFIG_HPP
# define CONFIG_HPP

#include <ServerConfig.hpp>
#include <vector>

class Config
{
	private:
		std::vector<ServerConfig>	_servers;
		Config(Config const& src);
		Config&	operator=(Config const& rhs);
	public:
		Config(void);
		~Config(void);

		//accessors
		std::vector<ServerConfig> const&	getServerConfig(void) const;
};

#endif //CONFIG_HPP