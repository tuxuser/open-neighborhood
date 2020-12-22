#pragma once

class Log
{
public:
	template<typename ...Args>
	static void Info(Args && ...args)
	{
		(std::cout << ... << args) << std::endl;
	}

	template<typename ...Args>
	static void Warn(Args && ...args)
	{
		std::cout << "\033[33m";
		(std::cout << ... << args) << "\033[0m" << std::endl;
	}

	template<typename ...Args>
	static void Success(Args && ...args)
	{
		std::cout << "\033[32m";
		(std::cout << ... << args) << "\033[0m" << std::endl;
	}

	template<typename ...Args>
	static void Error(Args && ...args)
	{
		std::cout << "\033[31m";
		(std::cout << ... << args) << "\033[0m" << std::endl;
	}
};

#define LOG_INFO(...) ::Log::Info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::Warn(__VA_ARGS__)
#define LOG_SUCCESS(...) ::Log::Success(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::Error(__VA_ARGS__)
