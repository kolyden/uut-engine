#include "Quaternion.h"
#include "Math.h"

namespace uut
{
	Quaternion::Quaternion()
	{
	}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	Quaternion Quaternion::operator=(const Quaternion& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		w = a.w;

		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& a) const
	{
		return Quaternion(x + a.x, y + a.y, z + a.z, w + a.w);
	}

	Quaternion& Quaternion::operator+=(const Quaternion& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;

		return *this;
	}

	Quaternion Quaternion::operator-(const Quaternion& a) const
	{
		return Quaternion(x - a.x, y - a.y, z - a.z, w - a.w);
	}

	Quaternion& Quaternion::operator-=(const Quaternion& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& a) const
	{
		return Quaternion(
			w*a.x + x*a.w + y*a.z - z*a.y,
			w*a.y + y*a.w + z*a.x - x*a.z,
			w*a.z + z*a.w + x*a.y - y*a.x,
			w*a.w - x*a.x - y*a.y - z*a.z);
	}

	Vector3 Quaternion::operator*(const Vector3& a) const
	{
		// result = this->Inverse() * idQuat( a.x, a.y, a.z, 0.0f ) * (*this)
		float xxzz = x*x - z*z;
		float wwyy = w*w - y*y;

		float xw2 = x*w*2.0f;
		float xy2 = x*y*2.0f;
		float xz2 = x*z*2.0f;
		float yw2 = y*w*2.0f;
		float yz2 = y*z*2.0f;
		float zw2 = z*w*2.0f;

		return Vector3(
			(xxzz + wwyy)*a.x + (xy2 + zw2)*a.y + (xz2 - yw2)*a.z,
			(xy2 - zw2)*a.x + (y*y + w*w - x*x - z*z)*a.y + (yz2 + xw2)*a.z,
			(xz2 + yw2)*a.x + (yz2 - xw2)*a.y + (wwyy - xxzz)*a.z);
	}

	Quaternion Quaternion::operator*(float a) const
	{
		return Quaternion(x * a, y * a, z * a, w * a);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& a)
	{
		*this = *this * a;

		return *this;
	}

	Quaternion& Quaternion::operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;

		return *this;
	}

	float Quaternion::Length() const
	{
		return Math::Sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion& Quaternion::Invert()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;

		return *this;
	}

	Quaternion Quaternion::Inverted() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion& Quaternion::Normalize()
	{
		const float len = this->Length();
		if (len)
		{
			const float ilength = 1 / len;
			x *= ilength;
			y *= ilength;
			z *= ilength;
			w *= ilength;
		}

		return *this;
	}

	Quaternion Quaternion::Normalized() const
	{
		Quaternion q(*this);
		q.Normalize();
		return q;
	}
}