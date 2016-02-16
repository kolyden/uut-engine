#pragma once
#include "Core/String.h"
#include "SDL2/SDL.h"

namespace uut
{
	enum class LogType
	{
		Debug,
		Info,
		Warning,
		Error,
		Critical,
	};

	class Debug
	{
	public:
		static void Log(LogType type, const char* message, ...);
	};
}