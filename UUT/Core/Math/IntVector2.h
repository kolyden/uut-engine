#pragma once
#include "Templates/Vector2Base.h"

namespace uut
{
	class Vector2;

	class IntVector2 : public Vector2Base<int>
	{
		UUT_VALUETYPE(uut, IntVector2, ValueType)
	public:
		constexpr IntVector2() : Vector2Base<int>(0, 0) {}
		constexpr IntVector2(int ix, int iy) : Vector2Base<int>(ix, iy) {}
		explicit constexpr IntVector2(int val) : Vector2Base<int>(val, val) {}
		constexpr IntVector2(const IntVector2& vec) : Vector2Base<int>(vec.x, vec.y) {}
		IntVector2(const Vector2& vec);

		IntVector2& operator += (const IntVector2& vec);
		IntVector2& operator -= (const IntVector2& vec);
		IntVector2& operator *= (int s);

		IntVector2 operator + () const;
		IntVector2 operator - () const;

		IntVector2 operator + (const IntVector2& vec) const;
		IntVector2 operator - (const IntVector2& vec) const;
		IntVector2 operator * (int s) const;

		friend IntVector2 operator * (int s, const IntVector2& vec) { return IntVector2(vec.x*s, vec.y*s); }

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }

		IntVector2& operator = (const IntVector2& vec);
		IntVector2& operator = (IntVector2&& vec);

		bool operator == (const IntVector2& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector2& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const IntVector2& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static const IntVector2 Default;
		static const IntVector2 Zero; // ( 0,  0)
		static const IntVector2 One;  // ( 1,  1)
		static const IntVector2 Left; // (-1,  0)
		static const IntVector2 Right;// ( 1,  0)
		static const IntVector2 Up;   // ( 0,  1)
		static const IntVector2 Down; // ( 0, -1)
	};

	static_assert(sizeof(IntVector2) == sizeof(int) * 2, "Invalid IntVector2 size");
	UUT_DEFAULT(IntVector2, IntVector2::Zero)
}