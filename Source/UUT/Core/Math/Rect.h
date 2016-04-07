#pragma once

namespace uut
{
	class IntRect;
	class Vector2;

	class Rect
	{
	public:
		Rect();
		Rect(const Vector2& pos, const Vector2& size);
		Rect(float x, float y, float width, float height);
		Rect(const Rect& rect);
		Rect(Rect&& rect);
		Rect(const IntRect& rect);

		float GetLeft() const { return x; }
		float GetRight() const { return x + width; }
		float GetBottom() const { return y; }
		float GetTop() const { return y + height; }

		Rect& operator =(const Rect& rect);
		Rect& operator =(Rect&& rect);

		bool operator == (const Rect& rect) const;
		bool operator != (const Rect& rect) const;

		static Rect FromLBRT(float left, float bottom, float right, float top);

		static const Rect Zero; // (0, 0, 0, 0)

		union
		{
			float data[4];
			struct
			{
				float x, y;
				float width;
				float height;
			};
		};
	};
}