#include "IntVector3.h"
#include <algorithm>
#include "Math.h"
#include "Vector3.h"
#include "IntVector2.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>
#include <Core/Math/Hash.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(IntVector3)
	{
		UUT_REGISTER_CTOR(int, int);
		UUT_REGISTER_CTOR(int, int, int);
		UUT_REGISTER_CTOR(IntVector2);
	}

	const IntVector3 IntVector3::Zero(0, 0, 0);
	const IntVector3 IntVector3::One(1, 1, 1);
	const IntVector3 IntVector3::Left(-1, 0, 0);
	const IntVector3 IntVector3::Right(1, 0, 0);
	const IntVector3 IntVector3::Up(0, 1, 0);
	const IntVector3 IntVector3::Down(0, -1, 0);
	const IntVector3 IntVector3::Forward(0, 0, 1);
	const IntVector3 IntVector3::Back(0, 0, -1);
	const IntVector3 IntVector3::AxisX(1, 0, 0);
	const IntVector3 IntVector3::AxisY(0, 1, 0);
	const IntVector3 IntVector3::AxisZ(0, 0, 1);

	IntVector3::IntVector3(const Vector3& vec)
		: Vector3Base<int>(
			Math::RoundToInt(vec.x),
			Math::RoundToInt(vec.y),
			Math::RoundToInt(vec.z))
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

	size_t IntVector3::GetHashCode() const
	{
		return Hash::Make<size_t>(x, y, z);
	}
}