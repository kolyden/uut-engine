#include "Vector3i.h"
#include <algorithm>
#include "Math.h"
#include "Vector3.h"
#include "Vector2i.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>
#include <Core/Math/Hash.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Vector3i)
	{
		UUT_REGISTER_CTOR(int, int);
		UUT_REGISTER_CTOR(int, int, int);
		UUT_REGISTER_CTOR(Vector2i);
	}

	const Vector3i Vector3i::Zero(0, 0, 0);
	const Vector3i Vector3i::One(1, 1, 1);
	const Vector3i Vector3i::Left(-1, 0, 0);
	const Vector3i Vector3i::Right(1, 0, 0);
	const Vector3i Vector3i::Up(0, 1, 0);
	const Vector3i Vector3i::Down(0, -1, 0);
	const Vector3i Vector3i::Forward(0, 0, 1);
	const Vector3i Vector3i::Back(0, 0, -1);
	const Vector3i Vector3i::AxisX(1, 0, 0);
	const Vector3i Vector3i::AxisY(0, 1, 0);
	const Vector3i Vector3i::AxisZ(0, 0, 1);

	Vector3i::Vector3i(const Vector3& vec)
		: Vector3Base<int>(
			Math::RoundToInt(vec.x),
			Math::RoundToInt(vec.y),
			Math::RoundToInt(vec.z))
	{
	}

	Vector3i& Vector3i::operator+=(const Vector3i& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3i& Vector3i::operator-=(const Vector3i& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3i& Vector3i::operator*=(int s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3i Vector3i::operator+() const
	{
		return *this;
	}

	Vector3i Vector3i::operator-() const
	{
		return Vector3i(-x, -y, -z);
	}

	Vector3i Vector3i::operator+(const Vector3i& vec) const
	{
		return Vector3i(x + vec.x, y + vec.y, z + vec.z);
	}

	Vector3i Vector3i::operator-(const Vector3i& vec) const
	{
		return Vector3i(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3i Vector3i::operator*(int s) const
	{
		return Vector3i(x * s, y * s, z * s);
	}

	size_t Vector3i::GetHashCode() const
	{
		return Hash::Make<size_t>(x, y, z);
	}
}