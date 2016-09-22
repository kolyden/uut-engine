#include "Color32.h"
#include "Color.h"
#include "Core/Math/Math.h"
#include <algorithm>

namespace uut
{
	const Color32 Color32::Clear(0, 0, 0, 0);
	const Color32 Color32::Transparent(255, 255, 255, 0);
	const Color32 Color32::White(255, 255, 255);
	const Color32 Color32::Black(0, 0, 0);
	const Color32 Color32::Red(255, 0, 0);
	const Color32 Color32::Green(0, 255, 0);
	const Color32 Color32::Blue(0, 0, 255);
	const Color32 Color32::Yellow(255, 255, 0, 255);
	const Color32 Color32::Magenta(255, 0, 255, 255);
	const Color32 Color32::Cyan(0, 255, 255, 255);
	const Color32 Color32::Gray(128, 128, 128, 255);
	const Color32 Color32::Silver(192, 192, 192, 255);

	Color32::Color32()
		: a(255), r(255), g(255), b(255)
	{
	}

	Color32::Color32(int _r, int _g, int _b, int _a /*= 255*/)
		: a(_a), r(_r), g(_g), b(_b)
	{
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

	bool Color32::operator==(const Color32& color) const
	{
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	bool Color32::operator!=(const Color32& color) const
	{
		return r != color.r || g != color.g || b != color.b || a != color.a;
	}

	uint32_t Color32::ToInt() const
	{
		return static_cast<uint32_t>((a << 24) | (r << 16) | (g << 8) | b);
	}

	Color32 Color32::FromRGBA(uint32_t argb)
	{
		return Color32(
			argb >> 24,
			(argb >> 16) & 0xFF,
			(argb >> 8) & 0xFF,
			argb & 0xFF);
	}

	Color32 Color32::FromABGR(uint32_t abgr)
	{
		return Color32(
			abgr & 0xFF,
			(abgr >> 8) & 0xFF,
			(abgr >> 16) & 0xFF,
			abgr >> 24);
	}
}