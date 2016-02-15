#pragma once
#include <cstdint>

namespace uut
{
	class Color32
	{
	public:
		union
		{
			uint32_t data;
			uint8_t m[4];
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

		Color32& operator=(const Color32& color);
		Color32& operator=(Color32&& color);

		static const Color32 EMPTY;
		static const Color32 WHITE;
		static const Color32 BLACK;
		static const Color32 GREEN;
		static const Color32 RED;
		static const Color32 BLUE;
	};
}