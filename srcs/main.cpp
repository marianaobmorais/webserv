#include <utils/Logger.hpp>

int	main()
{
	Logger::instance().log(INFO, "Program started.");
	Logger::instance().log(DEBUG, "Debugging information.");
	Logger::instance().log(ERROR, "An error occurred.");

	return 0;
}