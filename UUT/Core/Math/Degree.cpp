#include "Degree.h"
#include "Radian.h"
#include "Math.h"
#include <memory>
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	Degree operator"" _deg(long double angle)
	{
		return Degree(static_cast<float>(angle));
	}

	Degree operator"" _deg(unsigned long long int angle)
	{
		return Degree(static_cast<float>(angle));
	}

	///
	UUT_VALUETYPE_IMPLEMENT(Degree)
	{
		UUT_REGISTER_CTOR(float);
		UUT_REGISTER_CTOR(Radian);

		UUT_REGISTER_CONVERTER_DEFAULT(Radian);
		UUT_REGISTER_CONVERTER_FUNC(float, GetRadians);
	}

	const Degree Degree::Zero;

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
