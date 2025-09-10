#include <utils/Logger.hpp>

int	main()
{
	Logger logger("logfile.txt"); // Create logger instance

	// Example usage of the logger
	logger.log(INFO, "Program started.");
	logger.log(DEBUG, "Debugging information.");
	logger.log(ERROR, "An error occurred.");

	return 0;
}