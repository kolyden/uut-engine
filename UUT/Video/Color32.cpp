#include "Color32.h"
#include "Color.h"
#include "Core/Math/Math.h"
#include <algorithm>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Color32)
	{}

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
	const Color32 Color32::Grey(128, 128, 128, 255);
	const Color32 Color32::Silver(192, 192, 192, 255);

	Color32::Color32(const Color& color)
		: ColorBase<uint8_t>(
			Math::RoundToInt(color.r * 255),
			Math::RoundToInt(color.g * 255),
			Math::RoundToInt(color.b * 255),
			Math::RoundToInt(color.a * 255))
	{
	}

	Color32::Color32(uint32_t argb)
		: ColorBase<uint8_t>(
			(argb >> 16) & 0xFF,
			(argb >> 8) & 0xFF,
			argb & 0xFF,
			argb >> 24)
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