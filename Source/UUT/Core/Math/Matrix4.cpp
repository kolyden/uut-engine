#include "Matrix4.h"
#include "Vector3.h"
#include "Plane.h"
#include "Quaternion.h"
#include "Math.h"
#include <cstring>

namespace uut
{
	const Matrix4 Matrix4::Zero(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	const Matrix4 Matrix4::Identity(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4::Matrix4(
		float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44)
		: _11(f11), _12(f12), _13(f13), _14(f14)
		, _21(f21), _22(f22), _23(f23), _24(f24)
		, _31(f31), _32(f32), _33(f33), _34(f34)
		, _41(f41), _42(f42), _43(f43), _44(f44)
	{
	}

	Matrix4::Matrix4(const float* pf)
	{
	}

	float& Matrix4::operator()(int row, int col)
	{
		return m[row][col];
	}

	float Matrix4::operator()(int row, int col) const
	{
		return m[row][col];
	}

	Matrix4& Matrix4::operator*=(const Matrix4& mat)
	{
		*this = Multiply(*this, mat);
		return *this;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& mat)
	{
		_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
		_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
		_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
		_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& mat)
	{
		_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
		_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
		_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
		_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
		return *this;
	}

	Matrix4& Matrix4::operator*=(float f)
	{
		_11 *= f; _12 *= f; _13 *= f; _14 *= f;
		_21 *= f; _22 *= f; _23 *= f; _24 *= f;
		_31 *= f; _32 *= f; _33 *= f; _34 *= f;
		_41 *= f; _42 *= f; _43 *= f; _44 *= f;
		return *this;
	}

	Matrix4& Matrix4::operator/=(float f)
	{
		const float inv = 1.0f / f;
		_11 *= inv; _12 *= inv; _13 *= inv; _14 *= inv;
		_21 *= inv; _22 *= inv; _23 *= inv; _24 *= inv;
		_31 *= inv; _32 *= inv; _33 *= inv; _34 *= inv;
		_41 *= inv; _42 *= inv; _43 *= inv; _44 *= inv;
		return *this;
	}

	Matrix4 Matrix4::operator+() const
	{
		return *this;
	}

	Matrix4 Matrix4::operator-() const
	{
		return Matrix4(
			-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}

	Matrix4 Matrix4::operator*(const Matrix4& mat) const
	{
		return Multiply(*this, mat);
	}

	Matrix4 Matrix4::operator+(const Matrix4& mat) const
	{
		return Matrix4(
			_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
			_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
			_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
			_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
	}

	Matrix4 Matrix4::operator-(const Matrix4& mat) const
	{
		return Matrix4(
			_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
			_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
			_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
			_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
	}

	Matrix4 Matrix4::operator*(float f) const
	{
		return Matrix4(
			_11 * f, _12 * f, _13 * f, _14 * f,
			_21 * f, _22 * f, _23 * f, _24 * f,
			_31 * f, _32 * f, _33 * f, _34 * f,
			_41 * f, _42 * f, _43 * f, _44 * f);
	}

	Matrix4 Matrix4::operator/(float f) const
	{
		const float inv = 1.0f / f;
		return Matrix4(
			_11 * inv, _12 * inv, _13 * inv, _14 * inv,
			_21 * inv, _22 * inv, _23 * inv, _24 * inv,
			_31 * inv, _32 * inv, _33 * inv, _34 * inv,
			_41 * inv, _42 * inv, _43 * inv, _44 * inv);
	}

	Matrix4 operator*(float f, const Matrix4& mat)
	{
		return Matrix4(
			f * mat._11, f * mat._12, f * mat._13, f * mat._14,
			f * mat._21, f * mat._22, f * mat._23, f * mat._24,
			f * mat._31, f * mat._32, f * mat._33, f * mat._34,
			f * mat._41, f * mat._42, f * mat._43, f * mat._44);
	}

	bool Matrix4::operator==(const Matrix4& mat) const
	{
		return (memcmp(this, &mat, sizeof(Matrix4)) == 0);
	}

	bool Matrix4::operator!=(const Matrix4& mat) const
	{
		return (memcmp(this, &mat, sizeof(Matrix4)) != 0);
	}

	bool Matrix4::Decompose(Quaternion& rotation, Vector3& translation, Vector3& scale)
	{
		Vector3 vec;

		/*Compute the scaling part.*/
		vec.x = m[0][0];
		vec.y = m[0][1];
		vec.z = m[0][2];
		scale.x = vec.Length();

		vec.x = m[1][0];
		vec.y = m[1][1];
		vec.z = m[1][2];
		scale.y = vec.Length();

		vec.x = m[2][0];
		vec.y = m[2][1];
		vec.z = m[2][2];
		scale.z = vec.Length();

		/*Compute the translation part.*/
		translation.x = m[3][0];
		translation.y = m[3][1];
		translation.z = m[3][2];

		/*Let's calculate the rotation now*/
		if ((scale.x == 0.0f) || (scale.y == 0.0f) || (scale.z == 0.0f))
			return false;

		Matrix4 normalized;
		normalized.m[0][0] = m[0][0] / scale.x;
		normalized.m[0][1] = m[0][1] / scale.x;
		normalized.m[0][2] = m[0][2] / scale.x;
		normalized.m[1][0] = m[1][0] / scale.y;
		normalized.m[1][1] = m[1][1] / scale.y;
		normalized.m[1][2] = m[1][2] / scale.y;
		normalized.m[2][0] = m[2][0] / scale.z;
		normalized.m[2][1] = m[2][1] / scale.z;
		normalized.m[2][2] = m[2][2] / scale.z;

		rotation = Quaternion::RotationMatrix(normalized);
		return true;
	}

	float Matrix4::Determinant() const
	{
		float t[3], v[4];

		t[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		t[1] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		t[2] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		v[0] = m[1][1] * t[0] - m[2][1] * t[1] + m[3][1] * t[2];
		v[1] = -m[1][0] * t[0] + m[2][0] * t[1] - m[3][0] * t[2];

		t[0] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
		t[1] = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		t[2] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		v[2] = m[3][3] * t[0] - m[2][3] * t[1] + m[1][3] * t[2];
		v[3] = -m[3][2] * t[0] + m[2][2] * t[1] - m[1][2] * t[2];

		return m[0][0] * v[0] + m[0][1] * v[1] + 
			m[0][2] * v[2] + m[0][3] * v[3];
	}

	Matrix4 Matrix4::Transpose() const
	{
		Matrix4 out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) out.m[i][j] = m[j][i];
		return out;
	}

	Matrix4 Matrix4::Inverse(float* determinant /*= nullptr*/) const
	{
		float t[3], v[16];

		t[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		t[1] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		t[2] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		v[0] = m[1][1] * t[0] - m[2][1] * t[1] + m[3][1] * t[2];
		v[4] = -m[1][0] * t[0] + m[2][0] * t[1] - m[3][0] * t[2];

		t[0] = m[1][0] * m[2][1] - m[2][0] * m[1][1];
		t[1] = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		t[2] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		v[8] = m[3][3] * t[0] - m[2][3] * t[1] + m[1][3] * t[2];
		v[12] = -m[3][2] * t[0] + m[2][2] * t[1] - m[1][2] * t[2];

		float det = m[0][0] * v[0] + m[0][1] * v[4] +
			m[0][2] * v[8] + m[0][3] * v[12];

		if (det == 0.0f)
			return Zero;
		if (determinant != nullptr)
			*determinant = det;

		t[0] = m[2][2] * m[3][3] - m[2][3] * m[3][2];
		t[1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		t[2] = m[0][2] * m[2][3] - m[0][3] * m[2][2];
		v[1] = -m[0][1] * t[0] + m[2][1] * t[1] - m[3][1] * t[2];
		v[5] = m[0][0] * t[0] - m[2][0] * t[1] + m[3][0] * t[2];

		t[0] = m[0][0] * m[2][1] - m[2][0] * m[0][1];
		t[1] = m[3][0] * m[0][1] - m[0][0] * m[3][1];
		t[2] = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		v[9] = -m[3][3] * t[0] - m[2][3] * t[1] - m[0][3] * t[2];
		v[13] = m[3][2] * t[0] + m[2][2] * t[1] + m[0][2] * t[2];

		t[0] = m[1][2] * m[3][3] - m[1][3] * m[3][2];
		t[1] = m[0][2] * m[3][3] - m[0][3] * m[3][2];
		t[2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		v[2] = m[0][1] * t[0] - m[1][1] * t[1] + m[3][1] * t[2];
		v[6] = -m[0][0] * t[0] + m[1][0] * t[1] - m[3][0] * t[2];

		t[0] = m[0][0] * m[1][1] - m[1][0] * m[0][1];
		t[1] = m[3][0] * m[0][1] - m[0][0] * m[3][1];
		t[2] = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		v[10] = m[3][3] * t[0] + m[1][3] * t[1] + m[0][3] * t[2];
		v[14] = -m[3][2] * t[0] - m[1][2] * t[1] - m[0][2] * t[2];

		t[0] = m[1][2] * m[2][3] - m[1][3] * m[2][2];
		t[1] = m[0][2] * m[2][3] - m[0][3] * m[2][2];
		t[2] = m[0][2] * m[1][3] - m[0][3] * m[1][2];
		v[3] = -m[0][1] * t[0] + m[1][1] * t[1] - m[2][1] * t[2];
		v[7] = m[0][0] * t[0] - m[1][0] * t[1] + m[2][0] * t[2];

		v[11] = -m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) +
			m[1][0] * (m[0][1] * m[2][3] - m[0][3] * m[2][1]) -
			m[2][0] * (m[0][1] * m[1][3] - m[0][3] * m[1][1]);

		v[15] = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[1][0] * (m[0][1] * m[2][2] - m[0][2] * m[2][1]) +
			m[2][0] * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);

		det = 1.0f / det;

		Matrix4 out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.m[i][j] = v[4 * i + j] * det;

		return out;
	}

	Vector3 Matrix4::VectorTransform(const Vector3& v) const
	{
		const float norm = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3];
		return Vector3(
			(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0]) / norm,
			(m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1]) / norm,
			(m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2]) / norm);
	}

	Matrix4 Matrix4::Multiply(const Matrix4& m1, const Matrix4& m2)
	{
		Matrix4 out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
			}
		}

		return out;
	}

	Matrix4 Matrix4::LookAt(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		const Vector3 vec = (at - eye).Normalized();
		const Vector3 right = Vector3::Cross(up, vec).Normalized();
		const Vector3 upn = Vector3::Cross(vec, right).Normalized();

		Matrix4 u;
		u.m[0][0] = right.x;
		u.m[1][0] = right.y;
		u.m[2][0] = right.z;
		u.m[3][0] = -Vector3::Dot(right, eye);
		u.m[0][1] = upn.x;
		u.m[1][1] = upn.y;
		u.m[2][1] = upn.z;
		u.m[3][1] = -Vector3::Dot(upn, eye);
		u.m[0][2] = vec.x;
		u.m[1][2] = vec.y;
		u.m[2][2] = vec.z;
		u.m[3][2] = -Vector3::Dot(vec, eye);
		u.m[0][3] = 0.0f;
		u.m[1][3] = 0.0f;
		u.m[2][3] = 0.0f;
		u.m[3][3] = 1.0f;

		return u;
	}

	Matrix4 Matrix4::Ortho(float w, float h, float zn, float zf)
	{
		return Matrix4(
			2.0f / w, 0, 0, 0,
			0, 2.0f / h, 0, 0,
			0, 0, 1.0f / (zf - zn), 0,
			0, 0, zn / (zn - zf), 1);
	}

	Matrix4 Matrix4::OrthoOffCenter(float l, float r, float b, float t, float zn, float zf)
	{
		return Matrix4(
			2.0f / (r - l), 0, 0, 0,
			0, 2.0f / (t - b), 0, 0,
			0, 0, 1.0f / (zf - zn), 0,
			-1.0f - 2.0f*l / (r - l), 1.0f + 2.0f*t / (b - t), zn / (zn - zf), 1);
	}

	Matrix4 Matrix4::PerspectiveFov(const Radian& fovy, float aspect, float zn, float zf)
	{
		const float tan = Math::Tan(fovy / 2.0f);
		return Matrix4(
			1.0f / (aspect*tan), 0, 0, 0,
			0, 1.0f / tan, 0, 0,
			0, 0, zf / (zf - zn), 1.0f,
			0, 0, (zf*zn) / (zn - zf), 0);
	}

	Matrix4 Matrix4::Perspective(float w, float h, float zn, float zf)
	{
		return Matrix4(
			2.0f*zn / w, 0, 0, 0,
			0, 2.0f*zn / h, 0, 0,
			0, 0, zf / (zf - zn), 1,
			0, 0, (zn*zf) / (zn - zf), 0);
	}

	Matrix4 Matrix4::Reflect(const Plane& plane)
	{
		Plane Nplane = plane.Normalized();
		Matrix4 u = Identity;
		u.m[0][0] = 1.0f - 2.0f * Nplane.a * Nplane.a;
		u.m[0][1] = -2.0f * Nplane.a * Nplane.b;
		u.m[0][2] = -2.0f * Nplane.a * Nplane.c;
		u.m[1][0] = -2.0f * Nplane.a * Nplane.b;
		u.m[1][1] = 1.0f - 2.0f * Nplane.b * Nplane.b;
		u.m[1][2] = -2.0f * Nplane.b * Nplane.c;
		u.m[2][0] = -2.0f * Nplane.c * Nplane.a;
		u.m[2][1] = -2.0f * Nplane.c * Nplane.b;
		u.m[2][2] = 1.0f - 2.0f * Nplane.c * Nplane.c;
		u.m[3][0] = -2.0f * Nplane.d * Nplane.a;
		u.m[3][1] = -2.0f * Nplane.d * Nplane.b;
		u.m[3][2] = -2.0f * Nplane.d * Nplane.c;
		return u;
	}

	Matrix4 Matrix4::Translation(const Vector3& translation)
	{
		return Translation(translation.x, translation.y, translation.z);
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		return Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			x, y, z, 1);
	}

	Matrix4 Matrix4::RotationAxis(const Vector3& v, const Radian& angle)
	{
		const Vector3 nv = v.Normalized();
		const float sangle = Math::Sin(angle);
		const float cangle = Math::Cos(angle);
		const float cdiff = 1.0f - cangle;

		Matrix4 u;
		u.m[0][0] = cdiff * nv.x * nv.x + cangle;
		u.m[1][0] = cdiff * nv.x * nv.y - sangle * nv.z;
		u.m[2][0] = cdiff * nv.x * nv.z + sangle * nv.y;
		u.m[3][0] = 0.0f;
		u.m[0][1] = cdiff * nv.y * nv.x + sangle * nv.z;
		u.m[1][1] = cdiff * nv.y * nv.y + cangle;
		u.m[2][1] = cdiff * nv.y * nv.z - sangle * nv.x;
		u.m[3][1] = 0.0f;
		u.m[0][2] = cdiff * nv.z * nv.x - sangle * nv.y;
		u.m[1][2] = cdiff * nv.z * nv.y + sangle * nv.x;
		u.m[2][2] = cdiff * nv.z * nv.z + cangle;
		u.m[3][2] = 0.0f;
		u.m[0][3] = 0.0f;
		u.m[1][3] = 0.0f;
		u.m[2][3] = 0.0f;
		u.m[3][3] = 1.0f;

		return u;
	}

	Matrix4 Matrix4::RotationQuaternion(const Quaternion& q)
	{
		Matrix4 u = Identity;
		u.m[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		u.m[0][1] = 2.0f * (q.x *q.y + q.z * q.w);
		u.m[0][2] = 2.0f * (q.x * q.z - q.y * q.w);
		u.m[1][0] = 2.0f * (q.x * q.y - q.z * q.w);
		u.m[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		u.m[1][2] = 2.0f * (q.y *q.z + q.x *q.w);
		u.m[2][0] = 2.0f * (q.x * q.z + q.y * q.w);
		u.m[2][1] = 2.0f * (q.y *q.z - q.x *q.w);
		u.m[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		return u;
	}

	Matrix4 Matrix4::RotationX(const Radian& angle)
	{
		Matrix4 u = Identity;
		u.m[1][1] = Math::Cos(angle);
		u.m[2][2] = Math::Cos(angle);
		u.m[1][2] = Math::Sin(angle);
		u.m[2][1] = -Math::Sin(angle);
		return u;
	}

	Matrix4 Matrix4::RotationY(const Radian& angle)
	{
		Matrix4 u = Identity;
		u.m[0][0] = Math::Cos(angle);
		u.m[2][2] = Math::Cos(angle);
		u.m[0][2] = -Math::Sin(angle);
		u.m[2][0] = Math::Sin(angle);
		return u;
	}

	Matrix4 Matrix4::RotationZ(const Radian& angle)
	{
		Matrix4 u = Identity;
		u.m[0][0] = Math::Cos(angle);
		u.m[1][1] = Math::Cos(angle);
		u.m[0][1] = Math::Sin(angle);
		u.m[1][0] = -Math::Sin(angle);
		return u;
	}

	Matrix4 Matrix4::RotationYawPitchRoll(const Radian& yaw, const Radian& pitch, const Radian& roll)
	{
		const float sroll = Math::Sin(roll);
		const float croll = Math::Cos(roll);
		const float spitch = Math::Sin(pitch);
		const float cpitch = Math::Cos(pitch);
		const float syaw = Math::Sin(yaw);
		const float cyaw = Math::Cos(yaw);

		Matrix4 u;
		u.m[0][0] = sroll * spitch * syaw + croll * cyaw;
		u.m[0][1] = sroll * cpitch;
		u.m[0][2] = sroll * spitch * cyaw - croll * syaw;
		u.m[0][3] = 0.0f;
		u.m[1][0] = croll * spitch * syaw - sroll * cyaw;
		u.m[1][1] = croll * cpitch;
		u.m[1][2] = croll * spitch * cyaw + sroll * syaw;
		u.m[1][3] = 0.0f;
		u.m[2][0] = cpitch * syaw;
		u.m[2][1] = -spitch;
		u.m[2][2] = cpitch * cyaw;
		u.m[2][3] = 0.0f;
		u.m[3][0] = 0.0f;
		u.m[3][1] = 0.0f;
		u.m[3][2] = 0.0f;
		u.m[3][3] = 1.0f;
		return u;
	}

	Matrix4 Matrix4::Scaling(const Vector3& scale)
	{
		return Scaling(scale.x, scale.y, scale.z);
	}

	Matrix4 Matrix4::Scaling(float sx, float sy, float sz)
	{
		return Matrix4(
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1);
	}

	Matrix4 Matrix4::Transformation(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
	{
		return RotationQuaternion(rotation) * Translation(translation) * Scaling(scale);
	}
}