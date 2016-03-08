#include "Radian.h"
#include "Degree.h"
#include "Math.h"
#include <memory>

namespace uut
{
	const Radian Radian::EMPTY;

	Radian::Radian(const Degree& angle)
		: _angle(angle.GetRadians())
	{
	}

	float Radian::GetDegrees() const
	{
		return _angle * Math::RAD2DEG;
	}

	Radian& Radian::Clamp()
	{
		_angle = fmodf(_angle, Math::TWO_PI.GetRadians());
		if (_angle < 0)
			_angle += Math::TWO_PI.GetRadians();

		return *this;
	}

	Radian Radian::Clamped() const
	{
		Radian rad(_angle);
		rad.Clamp();
		return rad;
	}

	Radian& Radian::operator=(const Degree& d)
	{
		_angle = d.GetRadians();
		return *this;
	}

	Radian Radian::operator+(const Degree& d) const
	{
		return Radian(_angle + d.GetRadians());
	}

	Radian& Radian::operator+=(const Degree& d)
	{
		_angle += d.GetRadians();
		return *this;
	}

	Radian Radian::operator-(const Degree& d) const
	{
		return Radian(_angle - d.GetRadians());
	}

	Radian& Radian::operator-=(const Degree& d)
	{
		_angle -= d.GetRadians();
		return *this;
	}
}