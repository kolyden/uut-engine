#include "IntVector2.h"
#include <algorithm>

namespace uut
{
	const IntVector2 IntVector2::ZERO(0, 0);
	const IntVector2 IntVector2::ONE(1, 1);
	const IntVector2 IntVector2::AXIS_X(1, 0);
	const IntVector2 IntVector2::AXIS_Y(0, 1);

	IntVector2::IntVector2()
	{
	}

	IntVector2::IntVector2(int _x, int _y)
		: x(_x), y(_y)
	{
	}

	IntVector2::IntVector2(int val)
		: x(val), y(val)
	{
	}

	IntVector2::IntVector2(const IntVector2& vec)
		: x(vec.x), y(vec.y)
	{
	}

	IntVector2::IntVector2(IntVector2&& vec)
	{
		std::swap(x, vec.x);
		std::swap(y, vec.y);
	}

	IntVector2& IntVector2::operator=(const IntVector2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	IntVector2& IntVector2::operator=(IntVector2&& vec)
	{
		std::swap(x, vec.x);
		std::swap(y, vec.y);
		return *this;
	}
}