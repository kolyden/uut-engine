#pragma once
#include "Templates/RectBase.h"
#include "Vector2i.h"

namespace uut
{
	class Rect;

	class Recti : public RectBase<int>
	{
		UUT_VALUETYPE(uut, Recti, ValueType)
	public:
		constexpr Recti() : RectBase<int>(0, 0, 0, 0) {}

		constexpr Recti(int x, int y, int width, int height)
			: RectBase<int>(x, y, width, height) {}

		constexpr Recti(const Vector2i& pos, int width, int height)
			: RectBase<int>(pos.x, pos.y, width, height) {}

		constexpr Recti(int x, int y, const Vector2i& size)
			: RectBase<int>(x, y, size.x, size.y) {}

		constexpr Recti(const Vector2i& pos, const Vector2i& size)
			: RectBase<int>(pos.x, pos.y, size.x, size.y) {}

		constexpr Recti(const Recti& rect)
			: RectBase<int>(rect.x, rect.y, rect.width, rect.height) {}

		Recti(const Rect& rect);

		bool Intersect(const Vector2i& point) const { return IntersectPoint(point.x, point.y); }

		Recti& operator =(const Recti& rect);
		Recti& operator =(Recti&& rect);

		bool operator == (const Recti& rect) const;
		bool operator != (const Recti& rect) const;

		static Recti FromLBRT(int left, int bottom, int right, int top);

		static const Recti Zero; // (0, 0, 0, 0)
	};

	static_assert(sizeof(Recti) == sizeof(int) * 4, "Invalid Recti size");
	UUT_DEFAULT(Recti, Recti::Zero)
}