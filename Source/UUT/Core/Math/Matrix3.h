#pragma once
#include "Vector2.h"

namespace uut
{
	class Matrix4;

	class Matrix3
	{
	public:
		Matrix3() {}
		Matrix3(float _m00, float _m01, float _m02,
			float _m10, float _m11, float _m12,
			float _m20, float _m21, float _m22);

		void MakeZero();
		void MakeIdentity();

		operator float* () { return m; }
		operator const float* () const { return m; }

		float& operator[](unsigned int i) { return m[i]; }
		const float& operator[](unsigned int i) const { return m[i]; }

		Matrix3	operator + (const Matrix3& mat) const { Matrix3 m(*this); return m.Add(mat); }
		Matrix3	operator - (const Matrix3& mat) const { Matrix3 m(*this); return m.Sub(mat); }
		Matrix3	operator * (const Matrix3& mat) const { Matrix3 m(*this); return m.Multiply(mat); }
		Matrix3	operator / (const Matrix3& mat) const { Matrix3 m(*this); return m.Divide(mat); }

		Vector2	operator * (const Vector2& vec) const { Matrix3 m(*this); return m.Multiply(vec); }
		Vector2	operator / (const Vector2& vec) const { Matrix3 m(*this); return m.Divide(vec); }

		Matrix3	operator * (float f) const { Matrix3 m(*this); return m.Multiply(f); }
		Matrix3	operator / (float f) const { Matrix3 m(*this); return m.Divide(f); }

		Matrix3& operator += (const Matrix3& mat) { return Add(mat); }
		Matrix3& operator -= (const Matrix3& mat) { return Sub(mat); }
		Matrix3& operator *= (const Matrix3& mat) { return Multiply(mat); }
		Matrix3& operator /= (const Matrix3& mat) { return Divide(mat); }

		Vector2	operator *= (const Vector2& vec) { return Multiply(vec); }
		Vector2	operator /= (const Vector2& vec) { return Divide(vec); }

		void operator = (const Matrix3& mat);

		bool operator == (const Matrix3& mat) const { return IsEqual(mat); }
		bool operator != (const Matrix3& mat) const { return !IsEqual(mat); }

		bool IsZero() const;
		bool IsIdentity() const;

		float Det() const;
		Matrix3& Inverse();
		Matrix3& Adjoint();

		bool IsEqual(const Matrix3& mat) const;
		Matrix3& Add(const Matrix3& mat);
		Matrix3& Sub(const Matrix3& mat);
		Matrix3& Multiply(const Matrix3& mat);
		Matrix3& Divide(const Matrix3& mat);

		Vector2 Multiply(const Vector2& vec);
		Vector2 Divide(const Vector2& vec);

		Matrix3& Multiply(float f);
		Matrix3& Divide(float f);

		Matrix4 ToMat4() const;

		static Matrix3 Inverse(const Matrix3& mat);
		static Matrix3 Adjoint(const Matrix3& mat);
		static Matrix3 Orthonormalize(const Matrix3& mat);
		static Matrix3 Transpose(const Matrix3& mat);

		static Matrix3 Add(const Matrix3& a, const Matrix3& b) { Matrix3 dest = b + a; return dest; }
		static Matrix3 Sub(const Matrix3& a, const Matrix3& b) { Matrix3 dest = b - a; return dest; }
		static Matrix3 Multiply(const Matrix3& a, const Matrix3& b) { Matrix3 dest = b * a; return dest; }
		static Vector2 Multiply(const Matrix3& mat, const Vector2& vec) { Matrix3 dest(mat); return dest * vec; }

		static Matrix3 Translate(const Vector2& pos);
		static Matrix3 Translate(float dx, float dy);

		static Matrix3 RotateRad(float rot);
		static Matrix3 RotateDeg(float rot);

		static Matrix3 Scale(const Vector2& scale);
		static Matrix3 Scale(float scale);
		static Matrix3 Scale(float scalex, float scaley);

		static Matrix3 Transform(const Vector2& translate, float angleDeg, const Vector2& scale);
		static Matrix3 Transform(const Vector2& translate, float angleDeg, float scale);

		static const Matrix3 IDENTITY;
		static const Matrix3 ZERO;

		union
		{
			float m[9];
			struct
			{
				float m00, m01, m02;
				float m10, m11, m12;
				float m20, m21, m22;
			};
		};
	};
}