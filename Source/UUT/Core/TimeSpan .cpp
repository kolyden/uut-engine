#include "TimeSpan .h"

namespace uut
{
	static const int64_t TicksPerMilliseconds = 10000;
	static const int64_t TicksPerSecond = TicksPerMilliseconds * 1000;
	static const int64_t TicksPerMinute = TicksPerSecond * 60;
	static const int64_t TicksPerHour = TicksPerMinute * 60;
	static const int64_t TicksPerDay = TicksPerHour * 24;

	TimeSpan::TimeSpan(int64_t ticks)
		: _ticks(ticks)
	{
	}

	TimeSpan::TimeSpan(int hours, int minutes, int seconds)
	{
		_ticks = TimeToTicks(hours, minutes, seconds);
	}

	TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds)
		: TimeSpan(days, hours, minutes, seconds, 0)
	{
	}

	TimeSpan::TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds)
	{
		const int64_t num = (days * 3600L * 24L + hours * 3600L + minutes * 60L + seconds) * 1000L + milliseconds;
		_ticks = num * 10000L;
	}

	int TimeSpan::GetDays() const
	{
		return _ticks / TicksPerDay;
	}

	int TimeSpan::GetHours() const
	{
		return (_ticks / TicksPerHour) % 24;
	}

	int TimeSpan::GetMinutes() const
	{
		return (_ticks / TicksPerMinute) % 60;
	}

	int TimeSpan::GetSeconds() const
	{
		return (_ticks / TicksPerSecond) % 60;
	}

	int TimeSpan::GetMilliseconds() const
	{
		return (_ticks / TicksPerMilliseconds) % 1000;;
	}

	int64_t TimeSpan::GetTicks() const
	{
		return _ticks;
	}

	float TimeSpan::GetTotalDays() const
	{
		return static_cast<float>(_ticks) * 1.1574074074074074E-12;
	}

	float TimeSpan::GetTotalHours() const
	{
		return static_cast<float>(_ticks) * 2.7777777777777777E-11;
	}

	float TimeSpan::GetTotalMinutes() const
	{
		return static_cast<float>(_ticks) * 1.6666666666666667E-09;
	}

	float TimeSpan::GetTotalSeconds() const
	{
		return static_cast<float>(_ticks) * 1E-07;
	}

	TimeSpan TimeSpan::Add(const TimeSpan& ts) const
	{
		return TimeSpan(_ticks + ts._ticks);
	}

	TimeSpan TimeSpan::Subtract(const TimeSpan& ts) const
	{
		return TimeSpan(_ticks - ts._ticks);
	}

	int TimeSpan::CompareTo(const TimeSpan& ts) const
	{
		if (_ticks > ts._ticks)
			return 1;

		if (_ticks < ts._ticks)
			return -1;

		return 0;
	}

	int TimeSpan::Compare(const TimeSpan& ts1, const TimeSpan ts2)
	{
		if (ts1._ticks > ts2._ticks)
			return 1;

		if (ts1._ticks < ts2._ticks)
			return -1;

		return 0;
	}

	TimeSpan TimeSpan::FromDays(float days)
	{
		return Interval(days, 86400000);
	}

	TimeSpan TimeSpan::FromHours(float days)
	{
		return Interval(days, 3600000);
	}

	TimeSpan TimeSpan::FromMinutes(float days)
	{
		return Interval(days, 60000);
	}

	TimeSpan TimeSpan::FromSeconds(float days)
	{
		return Interval(days, 1000);
	}

	TimeSpan TimeSpan::FromMilliseconds(float days)
	{
		return Interval(days, 1);
	}

	///////////////////////////////////////////////////////////////////////////
	TimeSpan TimeSpan::Interval(float value, int scale)
	{
		const float num = value * static_cast<float>(scale) + (value >= 0.0f ? 0.5f : -0.5f);
		return TimeSpan(num * 10000L);
	}

	int64_t TimeSpan::TimeToTicks(int hours, int minutes, int seconds)
	{
		const int64_t num = hours * 3600L + minutes * 60L + seconds;
		return num * 10000000L;
	}
}