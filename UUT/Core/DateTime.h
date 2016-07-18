#pragma once
#include <chrono>
#include "String.h"

namespace uut
{
	class DateTime
	{
	public:
		typedef std::chrono::system_clock::time_point TimePoint;

		DateTime();
		DateTime(int year, int month, int day);
		DateTime(int year, int month, int day, int hour, int minute, int second);
		DateTime(int year, int month, int day, int hour, int minute, int second, int milisecond);
		explicit DateTime(int64_t ticks);
		explicit DateTime(const TimePoint& data);

		// A new object with the same date as this instance, and the time value set to 12:00:00 midnight (00:00:00).
		DateTime GetDate() const;

		int GetYear() const;
		int GetMonth() const;
		int GetDay() const;
		int GetHour() const;
		int GetMinute() const;
		int GetSecond() const;
		int GetMilisecond() const;

		String ToString() const;

		static DateTime Now();

	protected:
		TimePoint _time;
	};
}