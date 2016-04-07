#pragma once

namespace uut
{
	class Vector2;

	class Vector3
	{
	public:
		Vector3();
		explicit Vector3(float f);
		Vector3(float fx, float fy);
		Vector3(float fx, float fy, float fz);
		Vector3(const Vector2& v);

		operator float* () { return m; }
		operator const float* () const { return m; }
	
		Vector3& operator += (const Vector3& v);
		Vector3& operator -= (const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);

		Vector3 operator+() const;
		Vector3 operator-() const;

		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		Vector3 operator*(float s) const;
		Vector3 operator/(float s) const;

		friend Vector3 operator *(float s, const Vector3& vec);

		float Length() const;
		float LengthSqr() const;

		Vector3& Normalize();
		Vector3 Normalized() const;

		static Vector3 Add(const Vector3& v1, const Vector3& v2);
		static Vector3 Sub(const Vector3& v1, const Vector3& v2);

		static float Dot(const Vector3& a, const Vector3& b);
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		static Vector3 Lerp(const Vector3& a, const Vector3& b, float s);

		static Vector3 Maximize(const Vector3& a, const Vector3& b);
		static Vector3 Minimize(const Vector3& a, const Vector3& b);

		static Vector3 Scale(const Vector3& vec, float s);

		static float Distance(const Vector3& p0, const Vector3& p1);

		static const Vector3 Zero;   // ( 0,  0,  0)
		static const Vector3 One;    // ( 1,  1,  1)
		static const Vector3 Left;   // (-1,  0,  0)
		static const Vector3 Right;  // ( 1,  0,  0)
		static const Vector3 Up;     // ( 0,  1,  0)
		static const Vector3 Down;   // ( 0, -1,  0)
		static const Vector3 Forward;// ( 0,  0,  1)
		static const Vector3 Back;   // ( 0,  0, -1)

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