#pragma once
#include "IntVector2.h"

namespace uut
{
	class IntRect
	{
	public:
		static const IntRect EMPTY;

		union
		{
			int data[4];
			struct
			{
				int x, y;
				int width;
				int height;
			};
		};

		IntRect();
		IntRect(const IntVector2& pos, const IntVector2& size);
		IntRect(int x, int y, int width, int height);
		IntRect(const IntRect& rect);
		IntRect(IntRect&& rect);

		int GetLeft() const { return x; }
		int GetRight() const { return x + width; }
		int GetBottom() const { return y; }
		int GetTop() const { return y + height; }

		IntRect& operator =(const IntRect& rect);
		IntRect& operator =(IntRect&& rect);

		bool operator == (const IntRect& rect) const;
		bool operator != (const IntRect& rect) const;
	};
}