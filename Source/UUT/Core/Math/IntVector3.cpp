#include "IntVector3.h"
#include <algorithm>
#include "Math.h"
#include "Vector2.h"

namespace uut
{
	const IntVector3 IntVector3::Zero(0, 0, 0);
	const IntVector3 IntVector3::One(1, 1, 1);
	const IntVector3 IntVector3::Left(-1, 0, 0);
	const IntVector3 IntVector3::Right(1, 0, 0);
	const IntVector3 IntVector3::Up(0, 1, 0);
	const IntVector3 IntVector3::Down(0, -1, 0);
	const IntVector3 IntVector3::Forward(0, 0, 1);
	const IntVector3 IntVector3::Back(0, 0, -1);

	IntVector3::IntVector3()
	{
	}

	IntVector3::IntVector3(int ix, int iy, int iz)
		: x(ix), y(iy), z(iz)
	{
	}

	IntVector3::IntVector3(int val)
		: x(val), y(val)
	{
	}

	IntVector3::IntVector3(const IntVector3& vec)
		: x(vec.x)
		, y(vec.y)
	{
	}

	IntVector3::IntVector3(const Vector2& vec)
		: x(Math::RoundToInt(vec.x))
		, y(Math::RoundToInt(vec.y))
	{
	}

	IntVector3& IntVector3::operator+=(const IntVector3& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	IntVector3& IntVector3::operator-=(const IntVector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	IntVector3& IntVector3::operator*=(int s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	IntVector3 IntVector3::operator+() const
	{
		return *this;
	}

	IntVector3 IntVector3::operator-() const
	{
		return IntVector3(-x, -y, -z);
	}

	IntVector3 IntVector3::operator+(const IntVector3& vec) const
	{
		return IntVector3(x + vec.x, y + vec.y, z + vec.z);
	}

	IntVector3 IntVector3::operator-(const IntVector3& vec) const
	{
		return IntVector3(x - vec.x, y - vec.y, z - vec.z);
	}

	IntVector3 IntVector3::operator*(int s) const
	{
		return IntVector3(x * s, y * s, z * s);
	}

	IntVector3& IntVector3::operator=(const IntVector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

// 	IntVector3& IntVector3::operator=(IntVector3&& vec)
// 	{
// 		std::swap(x, vec.x);
// 		std::swap(y, vec.y);
// 		return *this;
// 	}
}