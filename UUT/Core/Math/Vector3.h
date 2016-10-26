#pragma once
#include "Templates/Vector3Base.h"
#include "Vector2.h"

namespace uut
{
	class IntVector3;

	class Vector3 : public Vector3Base<float>
	{
		UUT_VALUETYPE(uut, Vector3, ValueType)
	public:
		constexpr Vector3() : Vector3Base<float>(0, 0, 0) {}
		explicit constexpr Vector3(float val) : Vector3Base<float>(val, val, val) {}
		constexpr Vector3(float fx, float fy) : Vector3Base<float>(fx, fy, 0) {}
		constexpr Vector3(float fx, float fy, float fz) : Vector3Base<float>(fx, fy, fz) {}
		constexpr Vector3(const Vector2& v) : Vector3Base<float>(v.x, v.y, 0) {}
		Vector3(const IntVector3& vec);
	
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
		static const Vector3 AxisX;  // ( 1,  0,  0)
		static const Vector3 AxisY;  // ( 0,  1,  0)
		static const Vector3 AxisZ;  // ( 0,  0,  1)
		static const Vector3 Left;   // (-1,  0,  0)
		static const Vector3 Right;  // ( 1,  0,  0)
		static const Vector3 Up;     // ( 0,  1,  0)
		static const Vector3 Down;   // ( 0, -1,  0)
		static const Vector3 Forward;// ( 0,  0,  1)
		static const Vector3 Back;   // ( 0,  0, -1)
	};

	static_assert(sizeof(Vector3) == sizeof(float) * 3, "Invalid Vector3 size");
	UUT_DEFAULT(Vector3, Vector3::Zero)
}