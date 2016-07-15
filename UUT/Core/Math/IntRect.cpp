#include "IntRect.h"
#include <algorithm>
#include "Math.h"
#include "Rect.h"

namespace uut
{
	IntRect::IntRect()
	{
	}

	IntRect::IntRect(int _x, int _y, int _width, int _height)
		: x(_x), y(_y)
		, width(_width)
		, height(_height)
	{
	}

	IntRect::IntRect(const IntVector2& pos, int _width, int _height)
		: x(pos.x), y(pos.y)
		, width(_width)
		, height(_height)
	{
	}

	IntRect::IntRect(int _x, int _y, const IntVector2& size)
		: x(_x), y(_y)
		, width(size.x)
		, height(size.y)
	{
	}

	IntRect::IntRect(const IntVector2& pos, const IntVector2& size)
		: x(pos.x), y(pos.y)
		, width(size.x)
		, height(size.y)
	{
	}


	IntRect::IntRect(const IntRect& rect)
		: x(rect.x), y(rect.y)
		, width(rect.width)
		, height(rect.height)
	{
	}

	IntRect::IntRect(IntRect&& rect)
	{
		std::swap_ranges(data, data + 4, rect.data);
	}

	IntRect::IntRect(const Rect& rect)
		: x(Math::RoundToInt(rect.x))
		, y(Math::RoundToInt(rect.y))
		, width(Math::RoundToInt(rect.width))
		, height(Math::RoundToInt(rect.height))
	{
	}

	bool IntRect::Intersect(const IntVector2& point) const
	{
		return point.x >= x && point.x <= x + width &&
			point.y >= y && point.y <= y + height;
	}

	IntRect& IntRect::operator=(const IntRect& rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		return *this;
	}

	IntRect& IntRect::operator=(IntRect&& rect)
	{
		std::swap_ranges(data, data + 4, rect.data);
		return *this;
	}

	bool IntRect::operator==(const IntRect& rect) const
	{
		return x == rect.x&&y == rect.y&&width == rect.width&&height == rect.height;
	}

	bool IntRect::operator!=(const IntRect& rect) const
	{
		return !(*this == rect);
	}

	IntRect IntRect::FromLBRT(int left, int bottom, int right, int top)
	{
		return IntRect(left, bottom, right - left, top - bottom);
	}
}
