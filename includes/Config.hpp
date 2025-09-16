#ifndef CONFIG_H
# define CONFIG_H

#include <string>

class Config
{
	private:
		std::string	const _path;

		Config(Config const& src);
		Config&		operator=(Config const& rhs);
	public:
		Config(std::string file);
		~Config(void);

		void		lexer(void);
};

#endif //CONFIG_H