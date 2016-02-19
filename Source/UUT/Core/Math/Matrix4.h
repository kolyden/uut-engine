#pragma once
#include <cmath>

namespace uut
{
	class Vector3;

	class Matrix4
	{
	public:
		Matrix4();
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		explicit Matrix4(float* values);

		operator float*() { return &m[0][0]; }
		operator const float*() const { return &m[0][0]; }

		bool IsIdentity() const;

		void Transpose();
		Matrix4 Transposed() const;

		Matrix4 operator*(float s) const;
		Matrix4 operator+(const Matrix4& m) const;
		Matrix4 operator-(const Matrix4& m) const;
		Matrix4 operator*(const Matrix4& m) const;

		Matrix4& operator*=(float s);
		Matrix4& operator+=(const Matrix4& m);
		Matrix4& operator-=(const Matrix4& m);
		Matrix4& operator*=(const Matrix4& m);

		Vector3 Transform(const Vector3& v) const;
		Vector3 TransformDirection(const Vector3& v) const;

		static Matrix4 Translation(const Vector3& pos);
		static Matrix4 Translation(float x, float y, float z);

		static Matrix4 RotationAxis(const Vector3& axis, float angle);
		static Matrix4 Scale(const Vector3& scale);
		//static Matrix4 TRS(const Vector3& pos, )

		static Matrix4 LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up);

		static Matrix4 OrthoProjection(float width, float height, float znear, float zfar);
		static Matrix4 OrthoProjection(float left, float right, float bottom, float top, float znear, float zfar);

		static Matrix4 PerspectiveFovLH(float fovy, float aspect, float znear, float zfar);
		static Matrix4 PerspectiveLH(float width, float height, float znear, float zfar);

		static const Matrix4 EMPTY;
		static const Matrix4 IDENTITY;

	protected:
		class MVector4D
		{
		public:
			float x, y, z, w;

			float Length() const
			{
				return sqrt(x*x + y*y + z*z + w*w);
			}
		};

		union
		{
			float m[4][4];
			MVector4D v[4];
		};
	};
}
