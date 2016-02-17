#include "Debug.h"
#include <stdarg.h>

namespace uut
{
	void Debug::LogMessage(LogType type, const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		LogMessageV(type, message, args);
		va_end(args);
	}

	void Debug::LogMessageV(LogType type, const char* message, va_list args)
	{
		static const SDL_LogPriority convert[] = {
			SDL_LOG_PRIORITY_DEBUG, SDL_LOG_PRIORITY_INFO,
			SDL_LOG_PRIORITY_WARN, SDL_LOG_PRIORITY_ERROR,
			SDL_LOG_PRIORITY_CRITICAL
		};

		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			convert[static_cast<int>(type)], message, args);
	}

	void Debug::Log(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		LogMessageV(LogType::Info, message, args);
		va_end(args);
	}

	void Debug::LogDebug(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		LogMessageV(LogType::Debug, message, args);
		va_end(args);
	}

	void Debug::LogWarning(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		LogMessageV(LogType::Warning, message, args);
		va_end(args);
	}

	void Debug::LogError(const char* message, ...)
	{
		va_list args;
		va_start(args, message);
		LogMessageV(LogType::Error, message, args);
		va_end(args);
	}
}