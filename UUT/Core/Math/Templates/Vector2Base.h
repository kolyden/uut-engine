#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type>
	class Vector2Data
	{
	public:
		constexpr Vector2Data(Type fx, Type fy) : x(fx), y(fy) {}

		operator Type* () { return m; }
		operator const Type* () const { return m; }

		void Set(Type val) { x = val; y = val; }
		void Set(Type _x, int _y) { x = _x; y = _y; }

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

	template<typename Type, class VecType>
	class Vector2Logic
	{
	public:
		static VecType Add(const VecType& a, const VecType& b) { return VecType(a.x + b.x, a.y + b.y); }
		static VecType Sub(const VecType& a, const VecType& b) { return VecType(a.x - b.x, a.y - b.y); }
		static VecType Mul(const VecType& a, const VecType& b) { return VecType(a.x * b.x, a.y * b.y); }

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

		static Type DistanceSq(const VecType& a, const VecType& b)
		{
			return (b - a).LengthSq();
		}

		friend VecType operator * (Type s, const VecType& vec) { return VecType(vec.x*s, vec.y*s); }
	};
}