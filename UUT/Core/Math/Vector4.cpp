#include "Vector4.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Vector4)
	{}

	const Vector4 Vector4::Zero(0, 0, 0, 0);
	const Vector4 Vector4::One(1, 1, 1, 1);

	Vector4::Vector4()
	{
	}

	Vector4& Vector4::operator+=(const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	Vector4& Vector4::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}

	Vector4& Vector4::operator/=(float s)
	{
		x /= s;
		y /= s;
		z /= s;
		w /= z;
		return *this;
	}

	Vector4 Vector4::operator+() const
	{
		return *this;
	}

	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}

	Vector4 Vector4::operator+(const Vector4& v) const
	{
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	Vector4 Vector4::operator-(const Vector4& v) const
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vector4 Vector4::operator*(float s) const
	{
		return Vector4(x*s, y*s, z*s, w*s);
	}

	Vector4 Vector4::operator/(float s) const
	{
		return Vector4(x / s, y / s, z / s, w / s);
	}

	Vector4::Vector4(float fx, float fy, float fz, float fw)
		: x(fx), y(fy), z(fz), w(fw)
	{
	}
}