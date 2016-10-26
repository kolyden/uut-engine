#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type>
	class Vector2Base : public ValueType
	{
	public:
		constexpr Vector2Base(Type fx, Type fy) : x(fx), y(fy) {}

		operator Type* () { return m; }
		operator const Type* () const { return m; }

		Type Area() const { return x*y; }
		Type LengthSq() const { return x*x + y*y; }

		void AddValue(Type s) { x += s; y += s; }
		void SubValue(Type s) { x -= s; y -= s; }
		void MulValue(Type s) { x *= s; y *= s; }

		Type MaxValue() const { return x > y ? x : y; }
		Type MinValue() const { return x < y ? x : y; }

		union
		{
			Type m[2];
			struct
			{
				Type x;
				Type y;
			};
		};
	};
}