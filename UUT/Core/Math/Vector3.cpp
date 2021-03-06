#include "Vector3.h"
#include "Vector2.h"
#include "Vector3i.h"
#include <algorithm>
#include "Math.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Vector3)
	{
		UUT_REGISTER_CTOR(float, float);
		UUT_REGISTER_CTOR(float, float, float);
		UUT_REGISTER_CTOR(Vector2);
	}

	const Vector3 Vector3::Zero(0, 0, 0);
	const Vector3 Vector3::One(1, 1, 1);
	const Vector3 Vector3::AxisX(1, 0, 0);
	const Vector3 Vector3::AxisY(0, 1, 0);
	const Vector3 Vector3::AxisZ(0, 0, 1);
	const Vector3 Vector3::Left(-1, 0, 0);
	const Vector3 Vector3::Right(1, 0, 0);
	const Vector3 Vector3::Up(0, 1, 0);
	const Vector3 Vector3::Down(0, -1, 0);
	const Vector3 Vector3::Forward(0, 0, 1);
	const Vector3 Vector3::Back(0, 0, -1);

	Vector3::Vector3(const Vector3i& vec)
		: Vector3Base<float>(
			1.0f * vec.x,
			1.0f * vec.y,
			1.0f * vec.z)
	{
	}

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3 & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector3& Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	Vector3& Vector3::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	Vector3 Vector3::operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 Vector3::operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3 Vector3::operator*(float s) const
	{
		return Vector3(x*s, y*s, z*s);
	}

	Vector3 Vector3::operator/(float s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	Vector3 operator*(float s, const Vector3& vec)
	{
		return Vector3(vec.x*s, vec.y*s, vec.z*s);
	}

	float Vector3::Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	Vector3& Vector3::Normalize()
	{
		const float norm = Length();
		if (norm)
		{
			x /= norm;
			y /= norm;
			z /= norm;
		}
		else
		{
			x = 0;
			y = 0;
			z = 0;
		}

		return *this;
	}

	Vector3 Vector3::Normalized() const
	{
		const float norm = Length();
		if (norm)
		{
			return Vector3(
				x / norm,
				y / norm,
				z / norm);
		}

		return Zero;
	}

	Vector3 Vector3::Add(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(
			v1.x + v2.x,
			v1.y + v2.y,
			v1.z + v2.z);
	}

	Vector3 Vector3::Sub(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(
			v1.x - v2.x,
			v1.y - v2.y,
			v1.z - v2.z);
	}

	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}

	Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			a.y*b.z - a.z*b.y,
			a.z*b.x - a.x*b.z,
			a.x*b.y - a.y*b.x);
	}

	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float s)
	{
		return Vector3(
			(1 - s) * (a.x) + s * (b.x),
			(1 - s) * (a.y) + s * (b.y),
			(1 - s) * (a.z) + s * (b.z));
	}

	Vector3 Vector3::Maximize(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			a.x > b.x ? a.x : b.x,
			a.y > b.y ? a.y : b.y,
			a.z > b.z ? a.z : b.z);
	}

	Vector3 Vector3::Minimize(const Vector3& a, const Vector3& b)
	{
		return Vector3(
			a.x < b.x ? a.x : b.x,
			a.y < b.y ? a.y : b.y,
			a.z < b.z ? a.z : b.z);
	}

	Vector3 Vector3::Scale(const Vector3& vec, float s)
	{
		return Vector3(
			s*vec.x,
			s*vec.y,
			s*vec.z);
	}

	float Vector3::Distance(const Vector3& p0, const Vector3& p1)
	{
		return Math::Abs((p1 - p0).Length());
	}
}