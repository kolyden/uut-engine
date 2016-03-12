#pragma once

namespace uut
{
	class Vector2;

	class IntVector2
	{
	public:
		IntVector2();
		IntVector2(int ix, int iy);
		explicit IntVector2(int val);
		IntVector2(const IntVector2& vec);
		IntVector2(const Vector2& vec);

		operator int* () { return m; }
		operator const int* () const { return m; }

		IntVector2& operator += (const IntVector2& vec);
		IntVector2& operator -= (const IntVector2& vec);
		IntVector2& operator *= (int s);

		IntVector2 operator + () const;
		IntVector2 operator - () const;

		IntVector2 operator + (const IntVector2& vec) const;
		IntVector2 operator - (const IntVector2& vec) const;
		IntVector2 operator * (int s) const;

		friend IntVector2 operator * (int s, const IntVector2& vec) { return IntVector2(vec.x*s, vec.y*s); }

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }
		int Area() const { return x*y; }

		IntVector2& operator = (const IntVector2& vec);
		IntVector2& operator = (IntVector2&& vec);

		bool operator == (const IntVector2& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector2& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const IntVector2& vec) const { return x < vec.x && y < vec.y; }

		static const IntVector2 ZERO;
		static const IntVector2 ONE;
		static const IntVector2 AXIS_X;
		static const IntVector2 AXIS_Y;

		union
		{
			int m[2];
			struct
			{
				int x;
				int y;
			};
		};
	};
}