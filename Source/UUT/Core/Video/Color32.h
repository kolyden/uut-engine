#pragma once
#include <cstdint>

namespace uut
{
	class Color;

	class Color32
	{
	public:
		Color32();
		Color32(int r, int g, int b, int a = 255);
		Color32(const Color32& color);
		Color32(Color32&& color);
		Color32(const Color& color);
		explicit Color32(uint32_t argb);

		Color32& operator=(const Color32& color);
		Color32& operator=(Color32&& color);

		bool operator==(const Color32& color) const;
		bool operator!=(const Color32& color) const;

		uint32_t ToInt() const; // ARGB

		static Color32 FromRGBA(uint32_t argb);
		static Color32 FromABGR(uint32_t abgr);

		static const Color32 Clear;
		static const Color32 White;
		static const Color32 Black;
		static const Color32 Green;
		static const Color32 Red;
		static const Color32 Blue;

		union
		{
			uint8_t data[4];
			struct
			{
				uint8_t a;
				uint8_t r;
				uint8_t g;
				uint8_t b;
			};
		};
	};
}