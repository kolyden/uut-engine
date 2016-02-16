#pragma once

namespace uut
{
	class IntVector2
	{
	public:
		static const IntVector2 ZERO;
		static const IntVector2 ONE;
		static const IntVector2 AXIS_X;
		static const IntVector2 AXIS_Y;

		union
		{
			int data[2];
			struct
			{
				int x;
				int y;
			};
		};

		IntVector2();
		IntVector2(int x, int y);
		explicit IntVector2(int val);
		IntVector2(const IntVector2& vec);
		IntVector2(IntVector2&& vec);

		IntVector2& operator = (const IntVector2& vec);
		IntVector2& operator = (IntVector2&& vec);

		bool operator == (const IntVector2& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector2& vec) const { return x != vec.x || y != vec.y; }
	};
}