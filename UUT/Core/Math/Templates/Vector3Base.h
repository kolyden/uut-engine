#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type>
	class Vector3Base
	{
	public:
		constexpr Vector3Base(Type _x, Type _y, Type _z) : x(_x), y(_y), z(_z) {}

		operator Type* () { return m; }
		operator const Type* () const { return m; }

		Type Volume() const { return x*y*z; }
		Type LengthSqr() const { return x*x + y*y + z*z; }

		void AddValue(Type s) { x += s; y += s; z += s; }
		void SubValue(Type s) { x -= s; y -= s; z -= s; }
		void MulValue(Type s) { x *= s; y *= s; z *= s; }

		Type MaxValue() const { return (x > y ? (x > z ? x : z) : (y > z ? y : z)); }
		Type MinValue() const { return (x < y ? (x < z ? x : z) : (y < z ? y : z)); }

		union
		{
			Type m[3];
			struct
			{
				Type x;
				Type y;
				Type z;
			};
		};
	};
}