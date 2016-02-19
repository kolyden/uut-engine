#pragma once

namespace uut
{
	class Vector2;

	class Vector3
	{
	public:
		Vector3();
		explicit Vector3(float val);
		Vector3(float x, float y);
		Vector3(float x, float y, float z);
		Vector3(const Vector2& v);
	
		float Length() const;
		float LengthSqr() const;

		void Normalize();
		Vector3 Normalized() const;

		float Dot(const Vector3& v) const;
		Vector3 Cross(const Vector3& v) const;

		static float Dot(const Vector3& a, const Vector3& b);
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		Vector3 operator-() const;
		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(float s) const;
		Vector3 operator/(float s) const;

		Vector3& operator += (const Vector3& v);
		Vector3& operator -= (const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);

		static const Vector3 ZERO;
		static const Vector3 ONE;
		static const Vector3 AXIS_X;
		static const Vector3 AXIS_Y;
		static const Vector3 AXIS_Z;

		union
		{
			float m[3];
			struct
			{
				float x;
				float y;
				float z;
			};
		};
	};
}