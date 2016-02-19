#include "Vector3.h"
#include "Vector2.h"
#include <algorithm>

namespace uut
{
	const Vector3 Vector3::ZERO(0);
	const Vector3 Vector3::ONE(1);
	const Vector3 Vector3::AXIS_X(1, 0, 0);
	const Vector3 Vector3::AXIS_Y(0, 1, 0);
	const Vector3 Vector3::AXIS_Z(0, 0, 1);

	Vector3::Vector3()
	{
	}

	Vector3::Vector3(float val)
		: x(val), y(val) , z(val)
	{
	}

	Vector3::Vector3(float _x, float _y)
		: x(_x), y(_y), z(0)
	{
	}

	Vector3::Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	Vector3::Vector3(const Vector2& v)
		: x(v.x), y(v.y), z(0)
	{
	}

	float Vector3::Length() const
	{
		return sqrt(x*x + y*y + z*z);
	}

	float Vector3::LengthSqr() const
	{
		return (x*x + y*y + z*z);
	}

	void Vector3::Normalize()
	{
		(*this) /= Length();
	}

	Vector3 Vector3::Normalized() const
	{
		return (*this) / Length();
	}

	float Vector3::Dot(const Vector3& v) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	Vector3 Vector3::Cross(const Vector3& v) const
	{
		return Vector3(
			y*v.z - z*v.y,
			z*v.x - x*v.z,
			x*v.y - y*v.x);
	}

	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return a.Dot(b);
	}

	Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
	{
		return a.Cross(b);
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
}