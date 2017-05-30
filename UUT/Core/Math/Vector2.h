#pragma once
#include "Templates/Vector2Base.h"

namespace uut
{
	class Vector2i;

	class Vector2
		: public ValueType
		, public Vector2Data<float>
		, public Vector2Logic<float, Vector2>
	{
		UUT_VALUETYPE(uut, Vector2, ValueType)
	public:
		constexpr Vector2() : Vector2Data<float>(0, 0) {}
		constexpr Vector2(float fx, float fy) : Vector2Data<float>(fx, fy) {}
		explicit constexpr Vector2(float val) : Vector2Data<float>(val, val) {}
		Vector2(const Vector2i& vec);

		float Length() const;

		Vector2& Normalize();
		Vector2 Normalized() const;

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

		bool operator == (const Vector2& vec) const;
		bool operator != (const Vector2& vec) const;

		static float CCW(const Vector2& v1, const Vector2& v2);
		static float Dot(const Vector2& v1, const Vector2& v2);
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float s);

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