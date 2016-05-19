#pragma once
#include <Core/ValueType.h>
#include <Core/String.h>

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

	class Debug : public ValueType
	{
		UUT_STRUCT(Debug, ValueType)
	public:
		static void LogMessage(LogType type, const char* message, ...);
		static void LogMessageV(LogType type, const char* message, va_list args);

		static void Log(const char* message, ...);
		static void LogDebug(const char* message, ...);
		static void LogWarning(const char* message, ...);
		static void LogError(const char* message, ...);
	};
}