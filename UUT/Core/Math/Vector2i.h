#pragma once
#include "Templates/Vector2Base.h"

namespace uut
{
	class Vector2;

	class Vector2i
		: public ValueType
		, public Vector2Data<int>
		, public Vector2Logic<int, Vector2i>
	{
		UUT_VALUETYPE(uut, Vector2i, ValueType)
	public:
		constexpr Vector2i() : Vector2Data<int>(0, 0) {}
		constexpr Vector2i(int ix, int iy) : Vector2Data<int>(ix, iy) {}
		explicit constexpr Vector2i(int val) : Vector2Data<int>(val, val) {}
		constexpr Vector2i(const Vector2i& vec) : Vector2Data<int>(vec.x, vec.y) {}
		Vector2i(const Vector2& vec);

		float Length() const;

		Vector2i& operator += (const Vector2i& vec);
		Vector2i& operator -= (const Vector2i& vec);
		Vector2i& operator *= (int s);

		Vector2i operator + () const;
		Vector2i operator - () const;

		Vector2i operator + (const Vector2i& vec) const;
		Vector2i operator - (const Vector2i& vec) const;
		Vector2i operator * (int s) const;

		Vector2i& operator = (const Vector2i& vec);
		Vector2i& operator = (Vector2i&& vec);

		bool operator == (const Vector2i& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const Vector2i& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const Vector2i& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static Vector2i Lerp(const Vector2i& a, const Vector2i& b, float s);
		static float Distance(const Vector2i& a, const Vector2i& b);

		static const Vector2i Default;
		static const Vector2i Zero; // ( 0,  0)
		static const Vector2i One;  // ( 1,  1)
		static const Vector2i Left; // (-1,  0)
		static const Vector2i Right;// ( 1,  0)
		static const Vector2i Up;   // ( 0,  1)
		static const Vector2i Down; // ( 0, -1)
	};

	static_assert(sizeof(Vector2i) == sizeof(int) * 2, "Invalid Vector2i size");
	UUT_DEFAULT(Vector2i, Vector2i::Zero)
}