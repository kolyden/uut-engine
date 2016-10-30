#include "Color.h"
#include "Color32.h"
#include "Core/Math/Math.h"
#include <algorithm>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Color)
	{}

	static const float invInt = 1.0f / 255.0f;

	const Color Color::Clear(0, 0, 0, 0);
	const Color Color::White(1, 1, 1, 1);
	const Color Color::Black(0, 0, 0);
	const Color Color::Red(1, 0, 0);
	const Color Color::Green(0, 1, 0);
	const Color Color::Blue(0, 0, 1);

	Color::Color()
	{
	}

	Color::Color(float fr, float fg, float fb, float fa)
		: r(fr), g(fg), b(fb), a(fa)
	{
	}

	Color::Color(const Color32& color)
		: r(invInt * color.r)
		, g(invInt * color.g)
		, b(invInt * color.b)
		, a(invInt * color.a)
	{
	}

	Color::Color(const float* pf)
	{
		if (!pf) return;
		r = pf[0];
		g = pf[1];
		b = pf[2];
		a = pf[3];
	}

	Color::Color(uint32_t col)
	{
		const float f = 1.0f / 255.0f;
		r = f * (float)(unsigned char)(col >> 16);
		g = f * (float)(unsigned char)(col >> 8);
		b = f * (float)(unsigned char)col;
		a = f * (float)(unsigned char)(col >> 24);
	}

	Color::operator uint32_t() const
	{
		const uint32_t _r = r >= 1.0f ? 0xff : r <= 0.0f ? 0x00 : (uint32_t)(r * 255.0f + 0.5f);
		const uint32_t _g = g >= 1.0f ? 0xff : g <= 0.0f ? 0x00 : (uint32_t)(g * 255.0f + 0.5f);
		const uint32_t _b = b >= 1.0f ? 0xff : b <= 0.0f ? 0x00 : (uint32_t)(b * 255.0f + 0.5f);
		const uint32_t _a = a >= 1.0f ? 0xff : a <= 0.0f ? 0x00 : (uint32_t)(a * 255.0f + 0.5f);
		return (_a << 24) | (_r << 16) | (_g << 8) | _b;
	}

	Color& Color::operator+=(const Color& col)
	{
		r += col.r;
		g += col.g;
		b += col.b;
		a += col.a;
		return *this;
	}

	Color& Color::operator-=(const Color& col)
	{
		r -= col.r;
		g -= col.g;
		b -= col.b;
		a -= col.a;
		return *this;
	}

	Color& Color::operator*=(float f)
	{
		r *= f;
		g *= f;
		b *= f;
		a *= f;
		return *this;
	}

	Color& Color::operator/=(float f)
	{
		const float inv = 1.0f / f;
		r *= inv;
		g *= inv;
		b *= inv;
		a *= inv;
		return *this;
	}

	Color Color::operator+() const
	{
		return *this;
	}

	Color Color::operator-() const
	{
		return Color(-r, -g, -b, -a);
	}

	Color Color::operator+(const Color& col) const
	{
		return Color(r + col.r, g + col.g, b + col.b, a + col.a);
	}

	Color Color::operator-(const Color& col) const
	{
		return Color(r - col.r, g - col.g, b - col.b, a - col.a);
	}

	Color Color::operator*(float f) const
	{
		return Color(r * f, g * f, b * f, a * f);
	}

	Color Color::operator/(float f) const
	{
		const float inv = 1.0f / f;
		return Color(r * inv, g * inv, b * inv, a * inv);
	}

	Color operator*(float f, const Color& col)
	{
		return Color(f * col.r, f * col.g, f * col.b, f * col.a);
	}

	bool Color::operator==(const Color& col) const
	{
		return r == col.r && g == col.g && b == col.b && a == col.a;
	}

	bool Color::operator!=(const Color& col) const
	{
		return r != col.r || g != col.g || b != col.b || a != col.a;
	}

	Color Color::Negative() const
	{
		return Color(
			1.0f - r,
			1.0f - g,
			1.0f - b,
			a);
	}

	Color Color::Scale(float s) const
	{
		return Color(
			s*r,
			s*g,
			s*b,
			s*a);
	}

	Color& Color::AdjustContrast(float s)
	{
		r = 0.5f + s * (r - 0.5f);
		g = 0.5f + s * (g - 0.5f);
		b = 0.5f + s * (b - 0.5f);
		return *this;
	}

	Color& Color::AdjustSaturation(float s)
	{
		const float grey = r * 0.2125f + g * 0.7154f + b * 0.0721f;

		r = grey + s * (r - grey);
		g = grey + s * (g - grey);
		b = grey + s * (b - grey);
		return *this;
	}

	Color Color::Lerp(const Color& c1, const Color& c2, float s)
	{
		return Color(
			(1 - s) * (c1.r) + s *(c2.r),
			(1 - s) * (c1.g) + s *(c2.g),
			(1 - s) * (c1.b) + s *(c2.b),
			(1 - s) * (c1.a) + s *(c2.a));
	}

	Color Color::Modulate(const Color& c1, const Color& c2, float s)
	{
		return Color(
			(c1.r) * (c2.r),
			(c1.g) * (c2.g),
			(c1.b) * (c2.b),
			(c1.a) * (c2.a));
	}

	Color Color::Subtract(const Color& c1, const Color& c2)
	{
		return Color(
			c1.r - c2.r,
			c1.g - c2.g,
			c1.b - c2.b,
			c1.a - c2.a);
	}
}