#ifndef MBASE_LOGGER
#define MBASE_LOGGER

#include <iostream>
#include <string>

class Logger
{
public:
	static void Log(const std::string& key, const std::string& text)
	{
		std::cout << "[" << key << "] " << text << std::endl;
	}
};

#endif