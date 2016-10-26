#pragma once
#include "Templates/Vector3Base.h"
#include "IntVector2.h"

namespace uut
{
	class Vector3;

	class IntVector3 : public Vector3Base<int>
	{
		UUT_VALUETYPE(uut, IntVector3, ValueType)
	public:
		constexpr IntVector3() : Vector3Base<int>(0, 0, 0) {}
		explicit constexpr IntVector3(int val) : Vector3Base<int>(val, val, val) {}
		constexpr IntVector3(int ix, int iy) : Vector3Base<int>(ix, iy, 0) {}
		constexpr IntVector3(int ix, int iy, int iz) : Vector3Base<int>(ix, iy, iz) {}
		constexpr IntVector3(const IntVector2& vec) : Vector3Base<int>(vec.x, vec.y, 0) {}
		IntVector3(const Vector3& vec);

		IntVector3& operator += (const IntVector3& vec);
		IntVector3& operator -= (const IntVector3& vec);
		IntVector3& operator *= (int s);

		IntVector3 operator + () const;
		IntVector3 operator - () const;

		IntVector3 operator + (const IntVector3& vec) const;
		IntVector3 operator - (const IntVector3& vec) const;
		IntVector3 operator * (int s) const;

		friend IntVector3 operator * (int s, const IntVector3& vec) { return IntVector3(vec.x*s, vec.y*s, vec.z*s); }

		size_t GetHashCode() const;

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }

		bool operator == (const IntVector3& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector3& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const IntVector3& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static const IntVector3 Zero;   // ( 0,  0,  0)
		static const IntVector3 One;    // ( 1,  1,  1)
		static const IntVector3 Left;   // (-1,  0,  0)
		static const IntVector3 Right;  // ( 1,  0,  0)
		static const IntVector3 Up;     // ( 0,  1,  0)
		static const IntVector3 Down;   // ( 0, -1,  0)
		static const IntVector3 Forward;// ( 0,  0,  1)
		static const IntVector3 Back;   // ( 0,  0, -1)
		static const IntVector3 AxisX;  // ( 1,  0,  0)
		static const IntVector3 AxisY;  // ( 0,  1,  0)
		static const IntVector3 AxisZ;  // ( 0,  0,  1)
	};

	static_assert(sizeof(IntVector3) == sizeof(int) * 3, "Invalid IntVector3 size");
	UUT_DEFAULT(IntVector3, IntVector3::Zero)
}