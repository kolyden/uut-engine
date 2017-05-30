#pragma once
#include "Templates/Vector3Base.h"
#include "Vector2i.h"

namespace uut
{
	class Vector3;

	class Vector3i : public Vector3Base<int>
	{
		UUT_VALUETYPE(uut, Vector3i, ValueType)
	public:
		constexpr Vector3i() : Vector3Base<int>(0, 0, 0) {}
		explicit constexpr Vector3i(int val) : Vector3Base<int>(val, val, val) {}
		constexpr Vector3i(int ix, int iy) : Vector3Base<int>(ix, iy, 0) {}
		constexpr Vector3i(int ix, int iy, int iz) : Vector3Base<int>(ix, iy, iz) {}
		constexpr Vector3i(const Vector2i& vec) : Vector3Base<int>(vec.x, vec.y, 0) {}
		Vector3i(const Vector3& vec);

		Vector3i& operator += (const Vector3i& vec);
		Vector3i& operator -= (const Vector3i& vec);
		Vector3i& operator *= (int s);

		Vector3i operator + () const;
		Vector3i operator - () const;

		Vector3i operator + (const Vector3i& vec) const;
		Vector3i operator - (const Vector3i& vec) const;
		Vector3i operator * (int s) const;

		friend Vector3i operator * (int s, const Vector3i& vec) { return Vector3i(vec.x*s, vec.y*s, vec.z*s); }

		size_t GetHashCode() const;

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }

		bool operator == (const Vector3i& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const Vector3i& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const Vector3i& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static const Vector3i Zero;   // ( 0,  0,  0)
		static const Vector3i One;    // ( 1,  1,  1)
		static const Vector3i Left;   // (-1,  0,  0)
		static const Vector3i Right;  // ( 1,  0,  0)
		static const Vector3i Up;     // ( 0,  1,  0)
		static const Vector3i Down;   // ( 0, -1,  0)
		static const Vector3i Forward;// ( 0,  0,  1)
		static const Vector3i Back;   // ( 0,  0, -1)
		static const Vector3i AxisX;  // ( 1,  0,  0)
		static const Vector3i AxisY;  // ( 0,  1,  0)
		static const Vector3i AxisZ;  // ( 0,  0,  1)
	};

	static_assert(sizeof(Vector3i) == sizeof(int) * 3, "Invalid IntVector3 size");
	UUT_DEFAULT(Vector3i, Vector3i::Zero)
}