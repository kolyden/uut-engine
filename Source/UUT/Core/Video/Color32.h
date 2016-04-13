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
		Color32(const Color& color);
		explicit Color32(uint32_t argb);

		bool operator==(const Color32& color) const;
		bool operator!=(const Color32& color) const;

		uint32_t ToInt() const; // ARGB

		static Color32 FromRGBA(uint32_t argb);
		static Color32 FromABGR(uint32_t abgr);

		static const Color32 Clear;  // (  0,   0,   0, 255)
		static const Color32 White;  // (255, 255, 255, 255)
		static const Color32 Black;  // (  0,   0,   0, 255)
		static const Color32 Red;    // (255,   0,   0, 255)
		static const Color32 Green;  // (  0, 255,   0, 255)
		static const Color32 Blue;   // (  0,   0, 255, 255)

		static const Color32 Yellow; // (255, 255,   0, 255)
		static const Color32 Magenta;// (255,   0, 255, 255)
		static const Color32 Cyan;   // (  0, 255, 255, 255)

		static const Color32 Gray;   // (128, 128, 128, 255)
		static const Color32 Silver; // (192, 192, 192, 255)

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