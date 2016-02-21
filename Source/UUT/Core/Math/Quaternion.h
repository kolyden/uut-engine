#pragma once
#include "Vector3.h"

namespace uut
{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(float x, float y, float z, float w);

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
