#pragma once
#include <cstdint>

namespace uut
{
	class Color32;

	class Color
	{
	public:
		union
		{
			float data[4];
			struct
			{
				float a;
				float r;
				float g;
				float b;
			};
		};

		Color();
		Color(float r, float g, float b, float a = 1.0f);
		Color(const Color& color);
		Color(Color&& color);
		Color(const Color32& color);
		explicit Color(uint32_t color);

		Color& operator=(const Color& color);
		Color& operator=(Color&& color);

		uint32_t ToInt() const;

		static const Color EMPTY;
		static const Color WHITE;
		static const Color BLACK;
		static const Color GREEN;
		static const Color RED;
		static const Color BLUE;
	};
}