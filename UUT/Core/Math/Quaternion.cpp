#include "Quaternion.h"
#include "Math.h"
#include "Radian.h"
#include "Matrix4.h"

namespace uut
{
	const Quaternion Quaternion::Zero(0, 0, 0, 0);
	const Quaternion Quaternion::Identity(0, 0, 0, 1);

	Quaternion::Quaternion()
	{
	}

	Quaternion::Quaternion(float fx, float fy, float fz, float fw)
		: x(fx), y(fy), z(fz), w(fw)
	{
	}

	Quaternion::Quaternion(const Vector3& axis, const Radian& angle)
	{
		*this = RotationAxis(axis, angle);
	}

	Quaternion::Quaternion(const float* pf)
	{
		if (!pf) return;
		x = pf[0];
		y = pf[1];
		z = pf[2];
		w = pf[3];
	}

	Quaternion& Quaternion::operator+=(const Quaternion& quat)
	{
		x += quat.x;
		y += quat.y;
		z += quat.z;
		w += quat.w;
		return *this;
	}

	Quaternion& Quaternion::operator-=(const Quaternion& quat)
	{
		x -= quat.x;
		y -= quat.y;
		z -= quat.z;
		w -= quat.w;
		return *this;
	}

	Quaternion& Quaternion::operator*=(const Quaternion& quat)
	{
		*this = Multiply(*this, quat);
		return *this;
	}

	Quaternion& Quaternion::operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	Quaternion& Quaternion::operator/=(float f)
	{
		const float inv = 1.0f / f;
		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;
		return *this;
	}

	Quaternion Quaternion::operator+() const
	{
		return *this;
	}

	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x, -y, -z, -w);
	}

	Quaternion Quaternion::operator+(const Quaternion& quat) const
	{
		return Quaternion(x + quat.x, y + quat.y, z + quat.z, w + quat.w);
	}

	Quaternion Quaternion::operator-(const Quaternion& quat) const
	{
		return Quaternion(x - quat.x, y - quat.y, z - quat.z, w - quat.w);
	}

	Quaternion Quaternion::operator*(const Quaternion& quat) const
	{
		return Multiply(*this, quat);
	}

	Quaternion Quaternion::operator*(float f) const
	{
		return Quaternion(x * f, y * f, z * f, w * f);
	}

	Quaternion Quaternion::operator/(float f) const
	{
		const float inv = 1.0f / f;
		return Quaternion(x * inv, y * inv, z * inv, w * inv);
	}

	Quaternion operator*(float f, const Quaternion& quat)
	{
		return Quaternion(f * quat.x, f * quat.y, f * quat.z, f * quat.w);
	}

	bool Quaternion::operator==(const Quaternion& quat) const
	{
		return x == quat.x && y == quat.y && z == quat.z && w == quat.w;
	}

	bool Quaternion::operator!=(const Quaternion& quat) const
	{
		return x != quat.x || y != quat.y || z != quat.z || w != quat.w;
	}

	float Quaternion::Length() const
	{
		return Math::Sqrt(x*x + y*y + z*z + w*w);
	}

	float Quaternion::LengthSq() const
	{
		return x*x + y*y + z*z + w*w;
	}

	Quaternion& Quaternion::Normalize()
	{
		const float norm = Length();
		x /= norm;
		y /= norm;
		z /= norm;
		w /= norm;
		return *this;
	}

	Quaternion Quaternion::Normalized() const
	{
		const float norm = Length();
		return Quaternion(x / norm, y / norm, z / norm, w / norm);
	}

	Quaternion Quaternion::Conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion Quaternion::Inverse() const
	{
		const float norm = LengthSq();
		return Quaternion(-x / norm, -y / norm, -z / norm, w / norm);
	}

	void Quaternion::ToAxisAngle(Vector3& axis, Radian& angle) const
	{
		axis.x = x;
		axis.y = y;
		axis.z = z;
		angle = 2.0f*Math::Acos(w);
	}

	float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return (q1.x) * (q2.x) + (q1.y) * (q2.y) + (q1.z) * (q2.z) + (q1.w) * (q2.w);
	}

	Quaternion Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2)
	{
		return Quaternion(
			q2.w * q1.x + q2.x * q1.w + q2.y * q1.z - q2.z * q1.y,
			q2.w * q1.y - q2.x * q1.z + q2.y * q1.w + q2.z * q1.x,
			q2.w * q1.z + q2.x * q1.y - q2.y * q1.x + q2.z * q1.w,
			q2.w * q1.w - q2.x * q1.x - q2.y * q1.y - q2.z * q1.z);
	}

	Quaternion Quaternion::RotationAxis(const Vector3& axis, const Radian& angle)
	{
		const Vector3 temp = axis.Normalized();
		return Quaternion(
			Math::Sin(angle / 2.0f) * temp.x,
			Math::Sin(angle / 2.0f) * temp.y,
			Math::Sin(angle / 2.0f) * temp.z,
			Math::Cos(angle / 2.0f));
	}

	Quaternion Quaternion::RotationMatrix(const Matrix4& u)
	{
		const float trace = u.m[0][0] + u.m[1][1] + u.m[2][2] + 1.0f;
		if (trace > 1.0f)
		{
			const float s = 2.0f * Math::Sqrt(trace);
			return Quaternion(
				(u.m[1][2] - u.m[2][1]) / s,
				(u.m[2][0] - u.m[0][2]) / s,
				(u.m[0][1] - u.m[1][0]) / s,
				0.25f * s);
		}

		int maxi = 0;
		for (int i = 1; i < 3; i++)
		{
			if (u.m[i][i] > u.m[maxi][maxi])
				maxi = i;
		}

		float s;
		switch (maxi)
		{
		case 0:
			s = 2.0f * Math::Sqrt(1.0f + u.m[0][0] - u.m[1][1] - u.m[2][2]);
			return Quaternion(
				0.25f * s,
				(u.m[0][1] + u.m[1][0]) / s,
				(u.m[0][2] + u.m[2][0]) / s,
				(u.m[1][2] - u.m[2][1]) / s);

		case 1:
			s = 2.0f * Math::Sqrt(1.0f + u.m[1][1] - u.m[0][0] - u.m[2][2]);
			return Quaternion(
				(u.m[0][1] + u.m[1][0]) / s,
				0.25f * s,
				(u.m[1][2] + u.m[2][1]) / s,
				(u.m[2][0] - u.m[0][2]) / s);

		case 2:
			s = 2.0f * Math::Sqrt(1.0f + u.m[2][2] - u.m[0][0] - u.m[1][1]);
			return Quaternion(
				(u.m[0][2] + u.m[2][0]) / s,
				(u.m[1][2] + u.m[2][1]) / s,
				0.25f * s,
				(u.m[0][1] - u.m[1][0]) / s);
		}

		return Zero;
	}

	Quaternion Quaternion::RotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll)
	{
		const float syaw = Math::Sin(yaw / 2.0f);
		const float cyaw = Math::Cos(yaw / 2.0f);
		const float spitch = Math::Sin(pitch / 2.0f);
		const float cpitch = Math::Cos(pitch / 2.0f);
		const float sroll = Math::Sin(roll / 2.0f);
		const float croll = Math::Cos(roll / 2.0f);

		return Quaternion(
			syaw * cpitch * sroll + cyaw * spitch * croll,
			syaw * cpitch * croll - cyaw * spitch * sroll,
			cyaw * cpitch * sroll - syaw * spitch * croll,
			cyaw * cpitch * croll + syaw * spitch * sroll);
	}

	Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
	{
		float temp = 1.0f - t;
		float dot = Dot(q1, q2);
		if (dot < 0.0f)
		{
			t = -t;
			dot = -dot;
		}

		if (1.0f - dot > 0.001f)
		{
			const Radian theta = Math::Acos(dot);
			temp = Math::Sin(theta*temp) / Math::Sin(theta);
			t = Math::Sin(theta * t) / Math::Sin(theta);
		}

		return Quaternion(
			temp * q1.x + t * q2.x,
			temp * q1.y + t * q2.y,
			temp * q1.z + t * q2.z,
			temp * q1.w + t * q2.w);
	}
}