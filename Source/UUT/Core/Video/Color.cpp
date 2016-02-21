#include "Color.h"
#include "Color32.h"
#include "Core/Math/Math.h"
#include <algorithm>

namespace uut
{
	static const float invInt = 1.0f / 255.0f;

	const Color Color::EMPTY(0, 0, 0, 0);
	const Color Color::WHITE(1, 1, 1, 1);
	const Color Color::BLACK(0, 0, 0);
	const Color Color::GREEN(1, 0, 0);
	const Color Color::RED(0, 1, 0);
	const Color Color::BLUE(0, 0, 1);

	Color::Color()
	{
	}

	Color::Color(float _r, float _g, float _b, float _a)
		: a(_a), r(_r), g(_g), b(_b)
	{
	}

	Color::Color(const Color& color)
		: a(color.a), r(color.r), g(color.g), b(color.b)
	{

	}

	Color::Color(Color&& color)
	{
		std::swap_ranges(data, data + 4, color.data);
	}

	Color::Color(const Color32& color)
		: a(invInt*color.a)
		, r(invInt*color.r)
		, g(invInt*color.g)
		, b(invInt*color.b)
	{
	}

	Color::Color(uint32_t color)
	{
		*this = Color32(color);
	}

	Color& Color::operator=(const Color& color)
	{
		a = color.a;
		r = color.r;
		g = color.g;
		b = color.b;
		return *this;
	}

	Color& Color::operator=(Color&& color)
	{
		std::swap_ranges(data, data + 4, color.data);
		return *this;
	}

	uint32_t Color::ToInt() const
	{
		return Color32(*this).ToInt();
	}
}