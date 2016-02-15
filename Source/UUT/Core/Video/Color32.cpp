#include "Color32.h"
#include <algorithm>

namespace uut
{
	const Color32 Color32::EMPTY(0, 0, 0, 0);
	const Color32 Color32::WHITE(255, 255, 255);
	const Color32 Color32::BLACK(0, 0, 0);
	const Color32 Color32::RED(255, 0, 0);
	const Color32 Color32::GREEN(0, 255, 0);
	const Color32 Color32::BLUE(0, 0, 255);

	Color32::Color32()
		: r(255)
		, g(255)
		, b(255)
		, a(255)
	{
	}

	Color32::Color32(int _r, int _g, int _b, int _a /*= 255*/)
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a)
	{
	}

	Color32::Color32(const Color32& color)
		: data(color.data)
	{
	}

	Color32::Color32(Color32&& color)
	{
		std::swap(data, color.data);
	}

	Color32& Color32::operator=(const Color32& color)
	{
		data = color.data;
		return *this;
	}

	Color32& Color32::operator=(Color32&& color)
	{
		std::swap(data, color.data);
		return *this;
	}
}