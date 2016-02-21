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
		: a(255), r(255), g(255), b(255)
	{
	}

	Color32::Color32(int _r, int _g, int _b, int _a /*= 255*/)
		: a(_a), r(_r), g(_g), b(_b)
	{
	}

	Color32::Color32(const Color32& color)
		: a(color.a), r(color.r), g(color.g), b(color.b)
	{
	}

	Color32::Color32(Color32&& color)
	{
		std::swap_ranges(data, data + 4, color.data);
	}

	Color32::Color32(const Color& color)
		: a(Math::RoundToInt(color.a * 255))
		, r(Math::RoundToInt(color.r * 255))
		, g(Math::RoundToInt(color.g * 255))
		, b(Math::RoundToInt(color.b * 255))
	{
	}

	Color32::Color32(uint32_t argb)
		: a(argb >> 24)
		, r((argb >> 16) & 0xFF)
		, g((argb >> 8) & 0xFF)
		, b(argb & 0xFF)
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
		return static_cast<uint32_t>((a << 24) | (r << 16) | (g << 8) | b);
	}
}