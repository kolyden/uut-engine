#include "Quaternion.h"
#include "Math.h"
#include "Matrix3.h"
#include "Matrix4.h"

namespace uut
{
	const Quaternion Quaternion::ZERO(0, 0, 0, 0);
	const Quaternion Quaternion::IDENTITY(0, 0, 0, 1);

	Quaternion::Quaternion()
	{
	}

	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{
	}

	Quaternion::Quaternion(const Vector3& axis, float angle)
	{
		const float hangle = angle / 2.0f;
		float sin;
		Math::SinCos(hangle, sin, w);
		x = axis.x * sin;
		y = axis.y * sin;
		z = axis.z * sin;
	}

	void Quaternion::Set(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Quaternion::SetAngles(float _x, float _y, float _z)
	{
		float angle;

		angle = x * 0.5;
		const float sr = Math::Sin(angle);
		const float cr = Math::Cos(angle);

		angle = y * 0.5;
		const float sp = Math::Sin(angle);
		const float cp = Math::Cos(angle);

		angle = z * 0.5;
		const float sy = Math::Sin(angle);
		const float cy = Math::Cos(angle);

		const float cpcy = cp * cy;
		const float spcy = sp * cy;
		const float cpsy = cp * sy;
		const float spsy = sp * sy;

		x = (sr * cpcy - cr * spsy);
		y = (cr * spcy + sr * cpsy);
		z = (cr * cpsy - sr * spcy);
		w = (cr * cpcy + sr * spsy);

		Normalize();
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

	Matrix3 Quaternion::ToMat3() const
	{
		Matrix3	mat;
		float wx, wy, wz;
		float xx, yy, yz;
		float xy, xz, zz;
		float x2, y2, z2;

		x2 = x + x;
		y2 = y + y;
		z2 = z + z;

		xx = x * x2;
		xy = x * y2;
		xz = x * z2;

		yy = y * y2;
		yz = y * z2;
		zz = z * z2;

		wx = w * x2;
		wy = w * y2;
		wz = w * z2;

		mat.m00 = 1.0f - (yy + zz);
		mat.m01 = xy - wz;
		mat.m02 = xz + wy;

		mat.m10 = xy + wz;
		mat.m11 = 1.0f - (xx + zz);
		mat.m12 = yz - wx;

		mat.m20 = xz - wy;
		mat.m21 = yz + wx;
		mat.m22 = 1.0f - (xx + yy);

		return mat;
	}

	Matrix4 Quaternion::ToMat4() const
	{
		return ToMat3().ToMat4();
	}

	Quaternion Quaternion::FromEuler(float x, float y, float z)
	{
		Quaternion q;
		q.SetAngles(x, y, z);
		return q;
	}

	Quaternion Quaternion::FromEuler(const Vector3& angles)
	{
		return FromEuler(angles.x, angles.y, angles.z);
	}
}