#include "Rect.h"
#include <algorithm>
#include "Vector2.h"
#include "IntRect.h"

namespace uut
{
	const Rect Rect::Zero(0, 0, 0, 0);
	const Rect Rect::One(0, 0, 1, 1);

	Rect::Rect()
	{
	}

	Rect::Rect(const Vector2& pos, const Vector2& size)
		: x(pos.x), y(pos.y)
		, width(size.x)
		, height(size.y)
	{
	}

	Rect::Rect(float _x, float _y, float _width, float _height)
		: x(_x), y(_y)
		, width(_width)
		, height(_height)
	{
	}

	Rect::Rect(const Rect& rect)
		: x(rect.x), y(rect.y)
		, width(rect.width)
		, height(rect.height)
	{
	}

	Rect::Rect(Rect&& rect)
	{
		std::swap_ranges(data, data + 4, rect.data);
	}

	Rect::Rect(const IntRect& rect)
		: x(1.0f*rect.x)
		, y(1.0f*rect.y)
		, width(1.0f*rect.width)
		, height(1.0f*rect.height)
	{
	}

	Rect& Rect::operator=(const Rect& rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		return *this;
	}

	Rect& Rect::operator=(Rect&& rect)
	{
		std::swap_ranges(data, data + 4, rect.data);
		return *this;
	}

	bool Rect::operator==(const Rect& rect) const
	{
		return x == rect.x&&y == rect.y&&width == rect.width&&height == rect.height;
	}

	bool Rect::operator!=(const Rect& rect) const
	{
		return !(*this == rect);
	}

	Rect Rect::FromLBRT(float left, float bottom, float right, float top)
	{
		return Rect(left, bottom, right - left, top - bottom);
	}
}