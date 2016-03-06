#include "Degree.h"
#include "Radian.h"
#include "Math.h"
#include <memory>

namespace uut
{
	const Degree Degree::EMPTY;

	Degree::Degree(const Radian& angle)
		: _angle(angle.GetDegrees())
	{
	}

	float Degree::GetRadians() const
	{
		return _angle * Math::DEG2RAD;
	}

	Degree& Degree::Clamp()
	{
		_angle = fmodf(_angle, 360.0f);
		if (_angle < 0)
			_angle += 360.0f;

		return *this;
	}

	Degree Degree::Clamped() const
	{
		Degree deg(*this);
		deg.Clamp();
		return deg;
	}

	Degree& Degree::operator=(const Radian& r)
	{
		_angle = r.GetDegrees();
		return *this;
	}

	Degree Degree::operator+(const Radian& r) const
	{
		return Degree(_angle + r.GetDegrees());
	}

	Degree& Degree::operator+=(const Radian& r)
	{
		_angle += r.GetDegrees();
		return *this;
	}

	Degree Degree::operator-(const Radian& r) const
	{
		return Degree(_angle - r.GetDegrees());
	}

	Degree& Degree::operator-=(const Radian& r)
	{
		_angle -= r.GetDegrees();
		return *this;
	}
}