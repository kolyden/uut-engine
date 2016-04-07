#pragma once

namespace uut
{
	class Vector4
	{
	public:
		Vector4();
		Vector4(float x, float y, float z, float w);

		operator float* () { return m; }
		operator const float* () const { return m; }

		Vector4& operator += (const Vector4& v);
		Vector4& operator -= (const Vector4& v);
		Vector4& operator*=(float s);
		Vector4& operator/=(float s);

		Vector4 operator+() const;
		Vector4 operator-() const;

		Vector4 operator+(const Vector4& v) const;
		Vector4 operator-(const Vector4& v) const;
		Vector4 operator*(float s) const;
		Vector4 operator/(float s) const;

		static const Vector4 Zero;
		static const Vector4 One;

		union
		{
			float m[4];
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};
}