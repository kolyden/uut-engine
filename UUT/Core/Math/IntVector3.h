#pragma once
#include <Core/ValueType.h>

namespace uut
{
	class IntVector2;

	class IntVector3 : public ValueType
	{
		UUT_VALUETYPE(IntVector3, ValueType)
	public:
		IntVector3();
		explicit IntVector3(int val);
		IntVector3(int ix, int iy);
		IntVector3(int ix, int iy, int iz);
		IntVector3(const IntVector2& vec);

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

		IntVector2 ToVector2() const;
		size_t GetHashCode() const;

		void Set(int i) { x = i; y = i; }
		void Set(int ix, int iy) { x = ix; y = iy; }
		int Area() const { return x*y; }

		bool operator == (const IntVector3& vec) const { return x == vec.x && y == vec.y; }
		bool operator != (const IntVector3& vec) const { return x != vec.x || y != vec.y; }
		bool operator < (const IntVector3& vec) const { return (x < vec.x) || ((x == vec.x) && (y < vec.y));; }

		static const IntVector3 Zero;   // ( 0,  0,  0)
		static const IntVector3 One;    // ( 1,  1,  1)
		static const IntVector3 Left;   // (-1,  0,  0)
		static const IntVector3 Right;  // ( 1,  0,  0)
		static const IntVector3 Up;     // ( 0,  1,  0)
		static const IntVector3 Down;   // ( 0, -1,  0)
		static const IntVector3 Forward;// ( 0,  0,  1)
		static const IntVector3 Back;   // ( 0,  0, -1)

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

	UUT_DEFAULT(IntVector3, IntVector3::Zero)
}