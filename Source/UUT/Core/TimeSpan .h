#pragma once
#include "Platform.h"

namespace uut
{
	class TimeSpan
	{
	public:
		explicit TimeSpan(int64_t ticks);
		TimeSpan(int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds);
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds);

		int GetDays() const;
		int GetHours() const;
		int GetMinutes() const;
		int GetSeconds() const;
		int GetMilliseconds() const;
		int64_t GetTicks() const;

		float GetTotalDays() const;
		float GetTotalHours() const;
		float GetTotalMinutes() const;
		float GetTotalSeconds() const;

		TimeSpan Add(const TimeSpan& ts) const;
		TimeSpan Subtract(const TimeSpan& ts) const;
		int CompareTo(const TimeSpan& ts) const;

		static int Compare(const TimeSpan& ts1, const TimeSpan ts2);

		static TimeSpan FromDays(float days);
		static TimeSpan FromHours(float days);
		static TimeSpan FromMinutes(float days);
		static TimeSpan FromSeconds(float days);
		static TimeSpan FromMilliseconds(float days);

		static const TimeSpan Zero;

	protected:
		int64_t _ticks;

		static TimeSpan Interval(float value, int scale);
		static int64_t TimeToTicks(int hours, int minutes, int seconds);
	};
}