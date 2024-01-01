#ifndef MBASE_LOGGER
#define MBASE_LOGGER

#include <iostream>
#include <string>

class Logger
{
public:
	static void Log(const std::string& key, const std::string& text)
	{
#ifdef _DEBUG
		std::cout << "\x1B[37m" << "[" << key << "] " << text << "\033[0m" << std::endl;
#endif
	}

	static void Warning(const std::string& key, const std::string& text)
	{
#ifdef _DEBUG
		std::cout << "\x1B[33m" << "[" << key << "] " << text << "\033[0m" << std::endl;
#endif
	}

	static void Error(const std::string& key, const std::string& text)
	{
#ifdef _DEBUG
		std::cout << "\x1B[31m" << "[" << key << "] " << text << "\033[0m" << std::endl;
#endif
	}
};
#endif