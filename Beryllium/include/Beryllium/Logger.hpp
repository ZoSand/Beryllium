#ifndef BE_LOGGER_HPP
#define BE_LOGGER_HPP

#	include <Beryllium/API.hpp>
#	include <string>
#	include <streambuf>

namespace Beryllium
{
	enum class LogLevel
	{
		Trace,
		Info,
		Warn,
		Error,
		Critical
	};

	class BE_API Logger
	{
	public:

		static void Init();
		static void Shutdown();

		static void SetLevel(LogLevel _level);

		template <typename... Args>
		static void Trace(const std::string _message, Args... args);

		template <typename... Args>
		static void Info(const std::string _message, Args... args);

		template <typename... Args>
		static void Warn(const std::string _message, Args... args);

		template <typename... Args>
		static void Error(const std::string _message, Args... args);

		template <typename... Args>
		static void Critical(const std::string _message, Args... args);

	private:
		static LogLevel s_LogLevel;

		template <typename... Args>
		static void Print(const std::string _message, Args... args);

		//release and dist builds will write to a file instead of the console
		static std::streambuf* s_outBuffer;
		static std::streambuf* s_errBuffer;
		static std::ofstream* s_outStream;
	};
}

#	include <Beryllium/Logger.inl>

#endif // BE_LOGGER_HPP