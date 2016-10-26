#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type, class VecType>
	class Vector2Template : public ValueType
	{
	public:
		constexpr Vector2Template(Type fx, Type fy) : x(fx), y(fy) {}

		operator Type* () { return m; }
		operator const Type* () const { return m; }

		VecType& operator += (const VecType& vec) { x += vex.x; y += vec.y; return *this; }
		VecType& operator -= (const VecType& vec) { x -= vex.x; y -= vec.y; return *this; }
		VecType& operator *= (Type s) { x *= s; y *= s; return *this; }

		VecType operator + () const { return VecType(+x, +y); }
		VecType operator - () const { return VecType(-x, -y); }

		VecType operator + (const VecType& vec) const { return VecType(x + vec.x, y + vec.y); }
		VecType operator - (const VecType& vec) const { return VecType(x - vec.x, y - vec.y); }
		VecType operator * (float s) const { { return VecType(x * s, y * s); } }

		friend VecType operator * (Type s, const VecType& vec) { return VecType(vec.x*s, vec.y*s); }

		Type Area() const { return x*y; }
		Type LengthSq() const { return x*x + y*y; }

		static VecType Add(const VecType& v1, const VecType& v2) { return VecType(v1.x + v2.x, v1.y + v2.y); }
		static VecType Sub(const VecType& v1, const VecType& v2) { return VecType(v1.x - v2.x, v1.y - v2.y); }

		static VecType Maximize(const VecType& a, const VecType& b)
		{
			return VecType(
				a.x > b.x ? a.x : b.x,
				a.y > b.y ? a.y : b.y);
		}
		static VecType Minimize(const VecType& a, const VecType& b)
		{
			return VecType(
				a.x < b.x ? a.x : b.x,
				a.y < b.y ? a.y : b.y);
		}

		static VecType Scale(const VecType& vec, Type s) { return VecType(s*vec.x, s*vec.y); }
		static VecType Scale(const VecType& vec, const VecType& scale) { return VecType(scale.x*vec.x, scale.y*vec.y); }

		static const VecType Zero;  // ( 0,  0)
		static const VecType One;   // ( 1,  1)
		static const VecType Left;  // (-1,  0)
		static const VecType Right; // ( 1,  0)
		static const VecType Up;    // ( 0,  1)
		static const VecType Down;  // ( 0, -1)

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

	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::Zero(0, 0);
	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::One(1, 1);
	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::Left(-1, 0);
	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::Right(+1, 0);
	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::Up(0, +1);
	template<typename Type, class VecType> const VecType Vector2Template<Type, VecType>::Down(0, -1);
}