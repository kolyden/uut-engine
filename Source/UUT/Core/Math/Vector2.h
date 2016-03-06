#pragma once

namespace uut
{
	class IntVector2;

	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		explicit Vector2(float val);
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

		static const Vector2 ZERO;
		static const Vector2 ONE;
		static const Vector2 AXIS_X;
		static const Vector2 AXIS_Y;

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