#ifndef BE_LOGGER_INL
#define BE_LOGGER_INL

#	include <Beryllium/Logger.hpp>
#	include <iostream>

namespace Beryllium
{
	template<typename ...Args>
	inline void Logger::Trace(const std::string _message, Args ...args)
	{
		if (s_LogLevel <= LogLevel::Trace)
		{
			Logger::Print("[%8s] " + _message + "\n", "TRACE", args...);
		}
	}

	template<typename ...Args>
	inline void Logger::Info(const std::string _message, Args ...args)
	{
		if (s_LogLevel <= LogLevel::Info)
		{
			Logger::Print("[%8s] " + _message + "\n", "INFO", args...);
		}
	}

	template<typename ...Args>
	inline void Logger::Warn(const std::string _message, Args ...args)
	{
		if (s_LogLevel <= LogLevel::Warn)
		{
			Logger::Print("[%8s] " + _message + "\n", "WARNING", args...);
		}
	}

	template<typename ...Args>
	inline void Logger::Error(const std::string _message, Args ...args)
	{
		if (s_LogLevel <= LogLevel::Error)
		{
			Logger::Print("[%8s] " + _message + "\n", "ERROR", args...);
		}
	}

	template<typename ...Args>
	inline void Logger::Critical(const std::string _message, Args ...args)
	{
		if (s_LogLevel <= LogLevel::Critical)
		{
			Logger::Print("[%8s] " + _message + "\n", "CRITICAL", args...);
		}
	}

	template<typename ...Args>
	inline void Logger::Print(const std::string _message, Args ...args)
	{
		//parse the message like printf does and print it using cout (redirected to file if release or dist build)
		int size = std::snprintf(nullptr, 0, _message.c_str(), args...) + 1; // Extra space for '\0'
		if (size <= 0) {
			throw std::runtime_error("Error during formatting.");
		}
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, _message.c_str(), args...);
		std::cout << buf.get();
	}
}
#endif // BE_LOGGER_INL