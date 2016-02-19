#include "Vector2.h"
#include "IntVector2.h"

namespace uut
{
	const Vector2 Vector2::ZERO(0);
	const Vector2 Vector2::ONE(1);
	const Vector2 Vector2::AXIS_X(1, 0);
	const Vector2 Vector2::AXIS_Y(0, 1);

	Vector2::Vector2()
	{
	}

	Vector2::Vector2(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Vector2::Vector2(float val)
		: x(val), y(val)
	{
	}

	Vector2::Vector2(const IntVector2& vec)
		: x(static_cast<float>(vec.x))
		, y(static_cast<float>(vec.y))
	{
	}
}