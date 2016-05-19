#pragma once
#include "IntVector2.h"

namespace uut
{
	class Rect;

	class IntRect
	{
	public:
		IntRect();
		IntRect(const IntVector2& pos, const IntVector2& size);
		IntRect(int x, int y, int width, int height);
		IntRect(const IntRect& rect);
		IntRect(IntRect&& rect);
		IntRect(const Rect& rect);

		int GetLeft() const { return x; }
		int GetRight() const { return x + width; }
		int GetBottom() const { return y; }
		int GetTop() const { return y + height; }

		IntRect& operator =(const IntRect& rect);
		IntRect& operator =(IntRect&& rect);

		bool operator == (const IntRect& rect) const;
		bool operator != (const IntRect& rect) const;

		static IntRect FromLBRT(int left, int bottom, int right, int top);

		static const IntRect Zero; // (0, 0, 0, 0)

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
	};
}