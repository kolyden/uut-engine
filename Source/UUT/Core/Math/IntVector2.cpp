#include "IntVector2.h"
#include <algorithm>
#include "Math.h"
#include "Vector2.h"

namespace uut
{
	const IntVector2 IntVector2::Zero(0, 0);
	const IntVector2 IntVector2::One(1, 1);
	const IntVector2 IntVector2::Left(-1, 0);
	const IntVector2 IntVector2::Right(1, 0);
	const IntVector2 IntVector2::Up(0, 1);
	const IntVector2 IntVector2::Down(0, -1);

	IntVector2::IntVector2()
	{
	}

	IntVector2::IntVector2(int ix, int iy)
		: x(ix), y(iy)
	{
	}

	IntVector2::IntVector2(int val)
		: x(val), y(val)
	{
	}

	IntVector2::IntVector2(const IntVector2& vec)
		: x(vec.x)
		, y(vec.y)
	{
	}

	IntVector2::IntVector2(const Vector2& vec)
		: x(Math::RoundToInt(vec.x))
		, y(Math::RoundToInt(vec.y))
	{
	}

	IntVector2& IntVector2::operator+=(const IntVector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	IntVector2& IntVector2::operator-=(const IntVector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	IntVector2& IntVector2::operator*=(int s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	IntVector2 IntVector2::operator+() const
	{
		return *this;
	}

	IntVector2 IntVector2::operator-() const
	{
		return IntVector2(-x, -y);
	}

	IntVector2 IntVector2::operator+(const IntVector2& vec) const
	{
		return IntVector2(x + vec.x, y + vec.y);
	}

	IntVector2 IntVector2::operator-(const IntVector2& vec) const
	{
		return IntVector2(x - vec.x, y - vec.y);
	}

	IntVector2 IntVector2::operator*(int s) const
	{
		return IntVector2(x * s, y * s);
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
