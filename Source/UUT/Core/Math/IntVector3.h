#pragma once

namespace uut
{
	class Vector2;

	class IntVector3
	{
	public:
		IntVector3();
		IntVector3(int ix, int iy, int iz);
		explicit IntVector3(int val);
		IntVector3(const IntVector3& vec);
		IntVector3(const Vector2& vec);

		operator int* () { return m; }
		operator const int* () const { return m; }

		IntVector3& operator += (const IntVector3& vec);
		IntVector3& operator -= (const IntVector3& vec);
		IntVector3& operator *= (int s);

		IntVector3 operator + () const;
		IntVector3 operator - () const;

		IntVector3 operator + (const IntVector3& vec) const;
		IntVector3 operator - (const IntVector3& vec) const;
		IntVector3 operator * (int s) const;

		friend IntVector3 operator * (int s, const IntVector3& vec) { return IntVector3(vec.x*s, vec.y*s, vec.z*s); }

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }
		int Area() const { return x*y; }

		IntVector3& operator = (const IntVector3& vec);
// 		IntVector3& operator = (IntVector3&& vec);

		bool operator == (const IntVector3& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector3& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const IntVector3& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static const IntVector3 Zero;
		static const IntVector3 One;
		static const IntVector3 Left;
		static const IntVector3 Right;
		static const IntVector3 Up;
		static const IntVector3 Down;
		static const IntVector3 Forward;
		static const IntVector3 Back;

		union
		{
			int m[3];
			struct
			{
				int x;
				int y;
				int z;
			};
		};
	};
}