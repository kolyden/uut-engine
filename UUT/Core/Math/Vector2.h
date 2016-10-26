#pragma once
#include "Templates/Vector2Base.h"

namespace uut
{
	class IntVector2;

	class Vector2 : public Vector2Base<float>
	{
		UUT_VALUETYPE(uut, Vector2, ValueType)
	public:
		constexpr Vector2() : Vector2Base<float>(0, 0) {}
		constexpr Vector2(float fx, float fy) : Vector2Base<float>(fx, fy) {}
		explicit constexpr Vector2(float val) : Vector2Base<float>(val, val) {}
		Vector2(const IntVector2& vec);

		Vector2& operator += (const Vector2& vec);
		Vector2& operator -= (const Vector2& vec);
		Vector2& operator *= (float s);
		Vector2& operator /= (float s);

		Vector2 operator + () const;
		Vector2 operator - () const;

		Vector2 operator + (const Vector2& vec) const;
		Vector2 operator - (const Vector2& vec) const;
		Vector2 operator * (float s) const;
		Vector2 operator / (float s) const;

		friend Vector2 operator * (float s, const Vector2& vec) { return Vector2(vec.x*s, vec.y*s); }

		bool operator == (const Vector2& vec) const;
		bool operator != (const Vector2& vec) const;

		float Length() const;

		Vector2& Normalize();
		Vector2 Normalized() const;

		static Vector2 Add(const Vector2& v1, const Vector2& v2);
		static Vector2 Sub(const Vector2& v1, const Vector2& v2);

		static float CCW(const Vector2& v1, const Vector2& v2);
		static float Dot(const Vector2& v1, const Vector2& v2);
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float s);

		static Vector2 Maximize(const Vector2& a, const Vector2& b);
		static Vector2 Minimize(const Vector2& a, const Vector2& b);

		static Vector2 Scale(const Vector2& vec, float s);
		static Vector2 Scale(const Vector2& vec, const Vector2& scale);

		static float Distance(const Vector2& a, const Vector2& b);

		static const Vector2 Zero;  // ( 0,  0)
		static const Vector2 One;   // ( 1,  1)
		static const Vector2 Left;  // (-1,  0)
		static const Vector2 Right; // ( 1,  0)
		static const Vector2 Up;    // ( 0,  1)
		static const Vector2 Down;  // ( 0, -1)
	};

	static_assert(sizeof(Vector2) == sizeof(float) * 2, "Invalid Vector2 size");
	UUT_DEFAULT(Vector2, Vector2::Zero)
}