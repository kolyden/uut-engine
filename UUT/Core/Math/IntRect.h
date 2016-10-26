#pragma once
#include "Templates/RectBase.h"
#include "IntVector2.h"

namespace uut
{
	class Rect;

	class IntRect : public RectBase<int>
	{
		UUT_VALUETYPE(uut, IntRect, ValueType)
	public:
		constexpr IntRect() : RectBase<int>(0, 0, 0, 0) {}

		constexpr IntRect(int x, int y, int width, int height)
			: RectBase<int>(x, y, width, height) {}

		constexpr IntRect(const IntVector2& pos, int width, int height)
			: RectBase<int>(pos.x, pos.y, width, height) {}

		constexpr IntRect(int x, int y, const IntVector2& size)
			: RectBase<int>(x, y, size.x, size.y) {}

		constexpr IntRect(const IntVector2& pos, const IntVector2& size)
			: RectBase<int>(pos.x, pos.y, size.x, size.y) {}

		constexpr IntRect(const IntRect& rect)
			: RectBase<int>(rect.x, rect.y, rect.width, rect.height) {}

		IntRect(const Rect& rect);

		bool Intersect(const IntVector2& point) const { return IntersectPoint(point.x, point.y); }

		IntRect& operator =(const IntRect& rect);
		IntRect& operator =(IntRect&& rect);

		bool operator == (const IntRect& rect) const;
		bool operator != (const IntRect& rect) const;

		static IntRect FromLBRT(int left, int bottom, int right, int top);

		static const IntRect Zero; // (0, 0, 0, 0)
	};

	static_assert(sizeof(IntRect) == sizeof(int) * 4, "Invalid IntRect size");
	UUT_DEFAULT(IntRect, IntRect::Zero)
}