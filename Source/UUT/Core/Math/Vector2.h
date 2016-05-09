#pragma once
#include <Core/ValueType.h>

namespace uut
{
	class IntVector2;

	class Vector2 : public ValueType
	{
		UUT_STRUCT(Vector2, ValueType)
	public:
		constexpr Vector2() : x(0), y(0) {}
		constexpr Vector2(float fx, float fy) : x(fx), y(fy) {}
		explicit constexpr Vector2(float val) : x(val), y(val) {}
		Vector2(const IntVector2& vec);

		operator float* () { return m; }
		operator const float* () const { return m; }

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
		float LengthSq() const;

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

		static const Vector2 Default;
		static const Vector2 Zero;  // ( 0,  0)
		static const Vector2 One;   // ( 1,  1)
		static const Vector2 Left;  // (-1,  0)
		static const Vector2 Right; // ( 1,  0)
		static const Vector2 Up;    // ( 0,  1)
		static const Vector2 Down;  // ( 0, -1)

		union
		{
			float m[2];
			struct
			{
				float x;
				float y;
			};
		};
	};
}