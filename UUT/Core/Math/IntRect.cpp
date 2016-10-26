#include "IntRect.h"
#include <algorithm>
#include "Math.h"
#include "Rect.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(IntRect)
	{}

	const IntRect IntRect::Zero(0, 0, 0, 0);

	IntRect::IntRect(const Rect& rect)
		: RectBase<int>(
			Math::RoundToInt(rect.x),
			Math::RoundToInt(rect.y),
			Math::RoundToInt(rect.width),
			Math::RoundToInt(rect.height))
	{
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