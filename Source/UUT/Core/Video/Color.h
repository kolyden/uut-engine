#pragma once
#include <cstdint>

namespace uut
{
	class Color32;

	class Color
	{
	public:
		Color();
		Color(float fr, float fg, float fb, float fa = 1.0f);
		Color(const Color32& color);
		explicit Color(const float *pf);
		explicit Color(uint32_t color);

		operator uint32_t() const;
		operator float*() { return data; }
		operator const float*() const { return data; }

		Color& operator += (const Color& c);
		Color& operator -= (const Color& c);
		Color& operator *= (float f);
		Color& operator /= (float f);

		Color operator + () const;
		Color operator - () const;

		Color operator + (const Color& c) const;
		Color operator - (const Color& c) const;
		Color operator * (float f) const;
		Color operator / (float f) const;

		friend Color operator * (float f, const Color& c);

		bool operator == (const Color& c) const;
		bool operator != (const Color& c) const;

		Color Negative() const;
		Color Scale(float s) const;

		Color& AdjustContrast(float s);
		Color& AdjustSaturation(float s);

		static Color Lerp(const Color& c1, const Color& c2, float s);
		static Color Modulate(const Color& c1, const Color& c2, float s);
		static Color Subtract(const Color& c1, const Color& c2);

		static const Color Clear;
		static const Color White;
		static const Color Black;
		static const Color Green;
		static const Color Red;
		static const Color Blue;

		union
		{
			float data[4];
			struct
			{
				float r;
				float g;
				float b;
				float a;
			};
		};
	};
}