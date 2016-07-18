#include "DateTime.h"
#include <ratio>

namespace uut
{
	DateTime::DateTime()
	{
	}

	DateTime::DateTime(int year, int month, int day)
		: DateTime(year, month, day, 0, 0, 0)
	{
	}

	DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
	{
		tm timeinfo = tm();
		timeinfo.tm_year = year;
		timeinfo.tm_mon = month;
		timeinfo.tm_mday = day;
		timeinfo.tm_hour = hour;
		timeinfo.tm_min = minute;
		timeinfo.tm_sec = second;
		_time = std::chrono::system_clock::from_time_t(mktime(&timeinfo));
	}

	DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int milisecond)
		: DateTime(year, month, day, hour, minute, second)
	{
		_time += std::chrono::milliseconds(milisecond);
	}

	DateTime::DateTime(int64_t ticks)
	{
		_time += std::chrono::microseconds(ticks);
	}

	DateTime::DateTime(const TimePoint& data)
		: _time(data)
	{
	}

	DateTime DateTime::GetDate() const
	{
		return DateTime(GetYear(), GetMonth(), GetDay());
	}

	int DateTime::GetYear() const
	{
		return 0;
	}

	int DateTime::GetMonth() const
	{
		return 0;
	}

	int DateTime::GetDay() const
	{
		return 0;
	}

	int DateTime::GetHour() const
	{
		return 0;
	}

	int DateTime::GetMinute() const
	{
		return 0;
	}

	int DateTime::GetSecond() const
	{
		return 0;
	}

	int DateTime::GetMilisecond() const
	{
		return 0;
	}

	String DateTime::ToString() const
	{
		auto data = std::chrono::system_clock::to_time_t(_time);
		return ctime(&data);
	}

	DateTime DateTime::Now()
	{
		auto time_point = std::chrono::system_clock::now();
		return DateTime(time_point);
	}
}