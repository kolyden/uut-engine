#include "IntVector3.h"
#include <algorithm>
#include "Math.h"
#include "IntVector2.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_STRUCT_IMPLEMENT(IntVector3)
	{
		UUT_REGISTER_CTOR(int, int);
		UUT_REGISTER_CTOR(int, int, int);
		UUT_REGISTER_CTOR(IntVector2);
		UUT_REGISTER_CONVERTER_FUNC(IntVector2, ToVector2);
	}

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

	IntVector3::IntVector3(int ix, int iy)
		: x(ix), y(iy), z(0)
	{
	}

	IntVector3::IntVector3(int ix, int iy, int iz)
		: x(ix), y(iy), z(iz)
	{
	}

	IntVector3::IntVector3(int val)
		: x(val), y(val), z(val)
	{
	}

	IntVector3::IntVector3(const IntVector2& vec)
		: x(vec.x), y(vec.y), z(0)
	{
	}

	IntVector3& IntVector3::operator+=(const IntVector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	IntVector3& IntVector3::operator-=(const IntVector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	IntVector3& IntVector3::operator*=(int s)
	{
		x *= s;
		y *= s;
		z *= s;
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

// 	IntVector3& IntVector3::operator=(const IntVector3& vec)
// 	{
// 		x = vec.x;
// 		y = vec.y;
// 		z = vec.z;
// 		return *this;
// 	}

	IntVector2 IntVector3::ToVector2() const
	{
		return IntVector2(x, y);
	}
}