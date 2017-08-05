#pragma once
#include "Templates/RectBase.h"
#include "Vector2.h"

namespace uut
{
	class Recti;

	class Rect : public RectBase<float>
	{
		UUT_VALUETYPE(uut, Rect, ValueType)
	public:
		constexpr Rect() : RectBase<float>(0, 0, 0, 0) {}

		constexpr Rect(float x, float y, float width, float height)
			: RectBase<float>(x, y, width, height) {}

		constexpr Rect(const Vector2& pos, float width, float height)
			: RectBase<float>(pos.x, pos.y, width, height) {}

		constexpr Rect(float x, float y, const Vector2& size)
			: RectBase<float>(x, y, size.x, size.y) {}

		constexpr Rect(const Vector2& pos, const Vector2& size)
			: RectBase<float>(pos.x, pos.y, size.x, size.y) {}

		constexpr Rect(const Rect& rect)
			: RectBase<float>(rect.x, rect.y, rect.width, rect.height) {}

		Rect(const Recti& rect);

		bool Intersect(const Vector2& point) const { return IntersectPoint(point.x, point.y); }

		Rect& operator =(const Rect& rect);
		Rect& operator =(Rect&& rect);

		bool operator == (const Rect& rect) const;
		bool operator != (const Rect& rect) const;

		static Rect FromLBRT(float left, float bottom, float right, float top);

		static const Rect Zero; // (0, 0, 0, 0)
		static const Rect One; // (0, 0, 1, 1)
	};

	static_assert(sizeof(Rect) == sizeof(float) * 4, "Invalid Rect size");
	UUT_DEFAULT_VALUE(Rect, Rect::Zero)
}