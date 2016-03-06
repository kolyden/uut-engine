#pragma once
#include "Vector3.h"

namespace uut
{
	class Matrix4;
	class Radian;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float fx, float fy, float fz, float fw);
		Quaternion(const Vector3& axis, const Radian& angle);
		explicit Quaternion(const float* pf);

		operator float* () { return data; }
		operator const float* () const { return data; }

		Quaternion& operator += (const Quaternion& quat);
		Quaternion& operator -= (const Quaternion& quat);
		Quaternion& operator *= (const Quaternion& quat);
		Quaternion& operator *= (float f);
		Quaternion& operator /= (float f);

		Quaternion  operator + () const;
		Quaternion  operator - () const;

		Quaternion operator + (const Quaternion& quat) const;
		Quaternion operator - (const Quaternion& quat) const;
		Quaternion operator * (const Quaternion& quat) const;
		Quaternion operator * (float f) const;
		Quaternion operator / (float f) const;

		friend Quaternion operator * (float f, const Quaternion& quat);

		bool operator == (const Quaternion& quat) const;
		bool operator != (const Quaternion& quat) const;

		float Length() const;
		float LengthSq() const;

		Quaternion& Normalize();
		Quaternion Normalized() const;

		Quaternion Conjugate() const;
		Quaternion Inverse() const;

		void ToAxisAngle(Vector3& axis, Radian& angle) const;

		static float Dot(const Quaternion& q1, const Quaternion& q2);
		static Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
		static Quaternion RotationAxis(const Vector3& axis, const Radian& angle);
		static Quaternion RotationMatrix(const Matrix4& mat);
		static Quaternion RotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll);

		static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

		static const Quaternion ZERO;
		static const Quaternion IDENTITY;

		union
		{
			float data[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};
}
