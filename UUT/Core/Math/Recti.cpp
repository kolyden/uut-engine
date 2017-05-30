#include "Recti.h"
#include <algorithm>
#include "Math.h"
#include "Rect.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Recti)
	{}

	const Recti Recti::Zero(0, 0, 0, 0);

	Recti::Recti(const Rect& rect)
		: RectBase<int>(
			Math::RoundToInt(rect.x),
			Math::RoundToInt(rect.y),
			Math::RoundToInt(rect.width),
			Math::RoundToInt(rect.height))
	{
	}

	Recti& Recti::operator=(const Recti& rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		return *this;
	}

	Recti& Recti::operator=(Recti&& rect)
	{
		std::swap_ranges(data, data + 4, rect.data);
		return *this;
	}

	bool Recti::operator==(const Recti& rect) const
	{
		return x == rect.x&&y == rect.y&&width == rect.width&&height == rect.height;
	}

	bool Recti::operator!=(const Recti& rect) const
	{
		return !(*this == rect);
	}

	Recti Recti::FromLBRT(int left, int bottom, int right, int top)
	{
		return Recti(left, bottom, right - left, top - bottom);
	}
}