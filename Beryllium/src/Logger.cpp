#include <Beryllium/Logger.hpp>
#include <fstream>

namespace Beryllium
{
	LogLevel Logger::s_LogLevel = LogLevel::Trace;

	std::streambuf* Logger::s_outBuffer = nullptr;
	std::streambuf* Logger::s_errBuffer = nullptr;

	std::ofstream* Logger::s_outStream = nullptr;

	void Logger::Init()
	{
#	if defined(DIST) || defined(RELEASE)
		s_outStream = new std::ofstream("Beryllium.log", std::fstream::out | std::fstream::app);
		s_outBuffer = std::cout.rdbuf(s_outStream->rdbuf());
		s_errBuffer = std::cerr.rdbuf(s_outStream->rdbuf());
#	endif //DIST || RELEASE

#	if defined(DIST)
		s_LogLevel = LogLevel::Warn;
#	elif defined(RELEASE)
		s_LogLevel = LogLevel::Info;
#	else
		s_LogLevel = LogLevel::Trace;
#	endif
	}

	void Logger::Shutdown()
	{
#if defined(DIST) || defined(RELEASE)
		std::cout.rdbuf(s_outBuffer);
		std::cerr.rdbuf(s_errBuffer);

		s_outStream->close();
#endif
	}

	void Logger::SetLevel(LogLevel _level)
	{
		s_LogLevel = _level;
	}
}