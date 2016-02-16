#include "Color32.h"
#include "Color.h"
#include "Core/Math/Math.h"
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
		: r(255), g(255), b(255), a(255)
	{
	}

	Color32::Color32(int _r, int _g, int _b, int _a /*= 255*/)
		: r(_r), g(_g), b(_b), a(_a)
	{
	}

	Color32::Color32(const Color32& color)
		: r(color.r), g(color.g), b(color.b), a(color.a)
	{
	}

	Color32::Color32(Color32&& color)
	{
		std::swap_ranges(data, data + 4, color.data);
	}

	Color32::Color32(const Color& color)
		: r(Math::RoundToInt(color.r * 255))
		, g(Math::RoundToInt(color.g * 255))
		, b(Math::RoundToInt(color.b * 255))
		, a(Math::RoundToInt(color.a * 255))
	{
	}

	Color32::Color32(uint32_t color)
		: r(color >> 24)
		, g((color >> 16) & 0xFF)
		, b((color >> 8) & 0xFF)
		, a(color & 0xFF)
	{
	}

	Color32& Color32::operator=(const Color32& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}

	Color32& Color32::operator=(Color32&& color)
	{
		std::swap_ranges(data, data + 4, color.data);
		return *this;
	}


	uint32_t Color32::ToInt() const
	{
		return (r << 24) + (g << 16) + (b << 8) + a;
	}
}