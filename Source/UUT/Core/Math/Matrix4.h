#pragma once
#include <cstring>
#include "Vector3.h"

namespace uut
{
	class Quaternion;

	class Matrix4
	{
	public:
		Matrix4() {}
		Matrix4(float _m00, float _m01, float _m02, float _m03,
			float _m10, float _m11, float _m12, float _m13,
			float _m20, float _m21, float _m22, float _m23,
			float _m30, float _m31, float _m32, float _m33);

		void MakeZero();
		void MakeIdentity();

		operator float*() { return m; }
		operator const float*() const { return m; }

		float& operator[](unsigned int i) { return m[i]; }
		const float& operator[](unsigned int i) const { return m[i]; }

		Matrix4	operator + (const Matrix4& mat) const { Matrix4 m(*this); return m.Add(mat); }
		Matrix4	operator - (const Matrix4& mat) const { Matrix4 m(*this); return m.Sub(mat); }
		Matrix4	operator * (const Matrix4& mat) const { Matrix4 m(*this); return m.Multiply(mat); }

		Vector3 operator * (const Vector3& vec) const { Matrix4 m(*this); return m.Multiply(vec); }

		Matrix4	operator * (float f) const { Matrix4 m(*this); return m.Multiply(f); }
		Matrix4	operator / (float f) const { Matrix4 m(*this); return m.Divide(f); }

		Matrix4& operator += (const Matrix4& mat) { return Add(mat); }
		Matrix4& operator -= (const Matrix4& mat) { return Sub(mat); }
		Matrix4& operator *= (const Matrix4& mat) { return Multiply(mat); }

		Vector3 operator *= (const Vector3& vec) { return Multiply(vec); }

		void operator = (const Matrix4& mat) { memcpy(m, mat.m, sizeof(m)); }

		bool operator == (const Matrix4& mat) const { return IsEqual(mat); }
		bool operator != (const Matrix4& mat) const { return !IsEqual(mat); }

		bool IsZero() const;
		bool IsIdentity() const;

		float Det() const;
		Matrix4& Inverse();

		bool IsEqual(const Matrix4& mat) const;
		Matrix4& Add(const Matrix4& mat);
		Matrix4& Sub(const Matrix4& mat);
		Matrix4& Multiply(const Matrix4& mat);

		Vector3 Multiply(const Vector3& vec);

		Matrix4& Multiply(float f);
		Matrix4& Divide(float f);

		static Matrix4 Inverse(const Matrix4& mat);
		static Matrix4 Transpose(const Matrix4& mat);

		static Matrix4 Add(const Matrix4& a, const Matrix4& b) { Matrix4 dest = b + a; return dest; }
		static Matrix4 Sub(const Matrix4& a, const Matrix4& b) { Matrix4 dest = b - a; return dest; }
		static Matrix4 Multiply(const Matrix4& a, const Matrix4& b) { Matrix4 dest = b * a; return dest; }
		static Vector3 Multiply(const Matrix4& mat, const Vector3& vec) { Matrix4 dest(mat); return dest * vec; }

		static Matrix4 Translate(const Vector3& pos);
		static Matrix4 Translate(float dx, float dy, float dz);

		static Matrix4 RotateRad(const Vector3& axis, float angle);
		static Matrix4 RotateDeg(const Vector3& axis, float angle);

		static Matrix4 Scale(const Vector3& scale);
		static Matrix4 Scale(float scale);
		static Matrix4 Scale(float scalex, float scaley, float scalez);

		static Matrix4 Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

		static Matrix4 LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up);
		static Matrix4 OrthoProjection(float width, float height, float znear, float zfar);
		static Matrix4 OrthoProjection(float l, float r, float b, float t, float znear, float zfar);
		static Matrix4 PerspectiveFovLH(float fovy, float aspect, float znear, float zfar);
		static Matrix4 PerspectiveLH(float w, float h, float znear, float zfar);

		static const Matrix4 ZERO;
		static const Matrix4 IDENTITY;

		union
		{
			float m[16];
			float mtx[4][4];
			struct
			{
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
		};
	};
}