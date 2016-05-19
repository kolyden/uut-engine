#pragma once
#include "Vector3.h"

namespace uut
{
	class Plane;
	class Radian;
	class Quaternion;

	// row-major matrix
	class Matrix4
	{
	public:
		Matrix4() {}
		Matrix4(float f11, float f12, float f13, float f14,
			float f21, float f22, float f23, float f24,
			float f31, float f32, float f33, float f34,
			float f41, float f42, float f43, float f44);
		explicit Matrix4(const float* pf);

		float& operator () (int row, int col);
		float operator () (int row, int col) const;

		operator float*() { return data; }
		operator const float*() const { return data; }

		Matrix4& operator *= (const Matrix4& mat);
		Matrix4& operator += (const Matrix4& mat);
		Matrix4& operator -= (const Matrix4& mat);
		Matrix4& operator *= (float f);
		Matrix4& operator /= (float f);

		Matrix4 operator + () const;
		Matrix4 operator - () const;

		Matrix4 operator * (const Matrix4& mat) const;
		Matrix4 operator + (const Matrix4& mat) const;
		Matrix4 operator - (const Matrix4& mat) const;
		Matrix4 operator * (float f) const;
		Matrix4 operator / (float f) const;

		friend Matrix4 operator *(float f, const Matrix4& mat);

		bool operator == (const Matrix4& mat) const;
		bool operator != (const Matrix4& mat) const;

		bool Decompose(Quaternion& rotation, Vector3& translation, Vector3& scale);
		float Determinant() const;
		Matrix4 Transpose() const;
		Matrix4 Inverse(float* determinant = nullptr) const;

		Vector3 VectorTransform(const Vector3& vec) const;

		static Matrix4 Multiply(const Matrix4& m1, const Matrix4& m2);

		static Matrix4 LookAt(const Vector3& eye, const Vector3& at, const Vector3& up);
		static Matrix4 Ortho(float width, float height, float znear, float zfar);
		static Matrix4 OrthoOffCenter(float left, float right, float bottom, float top, float znear, float zfar);
		static Matrix4 PerspectiveFov(const Radian& fovy, float aspect, float znear, float zfar);
		static Matrix4 PerspectiveFov(const Radian& fovy, float width, float height, float znear, float zfar);
		static Matrix4 Perspective(float width, float height, float znear, float zfar);

		static Matrix4 Reflect(const Plane& plane);

		static Matrix4 Translation(const Vector3& translation);
		static Matrix4 Translation(float x, float y, float z);

		static Matrix4 RotationAxis(const Vector3& axis, const Radian& angle);
		static Matrix4 RotationQuaternion(const Quaternion& quat);
		static Matrix4 RotationX(const Radian& angle);
		static Matrix4 RotationY(const Radian& angle);
		static Matrix4 RotationZ(const Radian& angle);
		static Matrix4 RotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll);

		static Matrix4 Scaling(const Vector3& scale);
		static Matrix4 Scaling(float sx, float sy, float sz);

		static Matrix4 Transformation(const Vector3& translation, const Quaternion& rotation, const Vector3& scale);

		static const Matrix4 Zero;
		static const Matrix4 Identity;

		union
		{
			float data[16];
			float m[4][4];
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
		};
	};
}