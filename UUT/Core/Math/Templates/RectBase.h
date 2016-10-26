#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type>
	class RectBase : public ValueType
	{
	public:
		constexpr RectBase(Type _x, Type _y, Type _w, Type _h)
			: x(_x), y(_y), width(_w), height(_h) {}

		Type GetLeft() const { return x; }
		Type GetRight() const { return x + width; }
		Type GetBottom() const { return y; }
		Type GetTop() const { return y + height; }

		bool IntersectPoint(Type x, Type y) const
		{
			return x >= x && x <= x + width &&
				y >= y && y <= y + height;
		}

		union
		{
			Type data[4];
			struct
			{
				Type x, y;
				Type width;
				Type height;
			};
		};
	};
}