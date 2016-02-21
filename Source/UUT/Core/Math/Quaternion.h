#pragma once
#include "Vector3.h"

namespace uut
{
	class Matrix4;
	class Matrix3;

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3& axis, float angle);

		void Set(float x, float y, float z, float w);
		void SetAngles(float x, float y, float z);

		Quaternion operator-() const;
		Quaternion operator=(const Quaternion& quat);
		Quaternion operator+(const Quaternion& a) const;
		Quaternion& operator+=(const Quaternion& a);
		Quaternion operator-(const Quaternion& a) const;
		Quaternion& operator-=(const Quaternion &a);
		Quaternion operator*(const Quaternion& a) const;
		Vector3 operator*(const Vector3& a) const;
		Quaternion operator*(float a) const;
		Quaternion& operator*=(const Quaternion& a);
		Quaternion& operator*=(float a);

		float Length() const;

		Quaternion& Invert();
		Quaternion Inverted() const;

		Quaternion& Normalize();
		Quaternion Normalized() const;

		Matrix3 ToMat3() const;
		Matrix4 ToMat4() const;

		static Quaternion FromEuler(float x, float y, float z);
		static Quaternion FromEuler(const Vector3& angles);

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
