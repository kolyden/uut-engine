#include "Debug.h"
#include <stdarg.h>

namespace uut
{
	void Debug::Log(LogType type, const char* message, ...)
	{
		static const SDL_LogPriority convert[] = {
			SDL_LOG_PRIORITY_DEBUG, SDL_LOG_PRIORITY_INFO,
			SDL_LOG_PRIORITY_WARN, SDL_LOG_PRIORITY_ERROR,
			SDL_LOG_PRIORITY_CRITICAL
		};

		va_list args;
		va_start(args, message);
		SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
			convert[static_cast<int>(type)], message, args);
		va_end(args);
	}
}