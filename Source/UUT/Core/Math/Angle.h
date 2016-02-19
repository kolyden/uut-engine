#pragma once
#include "Math.h"

namespace uut
{
	enum AngleType
	{
		Degrees,
		Radians,
	};

	class Angle
	{
	public:
		Angle() : _radians(0) {}

		float deg() const { return Math::Rad2Deg * _radians; }
		float rad() const { return _radians; }

	protected:
		float _radians;
	};
}