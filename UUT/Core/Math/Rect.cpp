#include "Rect.h"
#include <algorithm>
#include "Vector2.h"
#include "Recti.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Rect)
	{}

	const Rect Rect::Zero(0, 0, 0, 0);
	const Rect Rect::One(0, 0, 1, 1);

	Rect::Rect(const Recti& rect)
		: RectBase<float>(1.0f*rect.x, 1.0f*rect.y, 1.0f*rect.width, 1.0f*rect.height)
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