#pragma once
#include <cstdint>

namespace uut
{
	class Color;

	class Color32
	{
	public:
		union
		{
			uint8_t data[4];
			struct
			{
				uint8_t r;
				uint8_t g;
				uint8_t b;
				uint8_t a;
			};
		};

		Color32();
		Color32(int r, int g, int b, int a = 255);
		Color32(const Color32& color);
		Color32(Color32&& color);
		Color32(const Color& color);
		explicit Color32(uint32_t color);

		Color32& operator=(const Color32& color);
		Color32& operator=(Color32&& color);

		uint32_t ToInt() const;

		static const Color32 EMPTY;
		static const Color32 WHITE;
		static const Color32 BLACK;
		static const Color32 GREEN;
		static const Color32 RED;
		static const Color32 BLUE;
	};
}