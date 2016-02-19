#include "Matrix4.h"
#include "Vector3.h"
#include "Math.h"
#include <cstring>

namespace uut
{
	const Matrix4 Matrix4::EMPTY(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	const Matrix4 Matrix4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4::Matrix4()
	{
	}

	Matrix4::Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	}

	Matrix4::Matrix4(float* values)
	{
		memcpy(&m[0][0], values, sizeof(float) * 16);
	}

	bool Matrix4::IsIdentity() const
	{
		if (!(m[0][0] == 1 && m[1][1] == 1 && m[2][2] == 1 && m[3][3] == 1))
			return false;

		if (!(m[0][1] == 0 && m[0][2] == 0 && m[0][3] == 0))
			return false;

		if (!(m[1][0] == 0 && m[1][2] == 0 && m[1][3] == 0))
			return false;

		if (!(m[2][0] == 0 && m[2][1] == 0 && m[2][3] == 0))
			return false;

		if (!(m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0))
			return false;

		return true;
	}

	void Matrix4::Transpose()
	{
		m[0][0] = m[0][0]; m[1][0] = m[0][1]; m[2][0] = m[0][2]; m[3][0] = m[0][3];
		m[0][1] = m[1][0]; m[1][1] = m[1][1]; m[2][1] = m[1][2]; m[3][1] = m[1][3];
		m[0][2] = m[2][0]; m[1][2] = m[2][1]; m[2][2] = m[2][2]; m[3][2] = m[2][3];
		m[0][3] = m[3][0]; m[1][3] = m[3][1]; m[2][3] = m[3][2]; m[3][3] = m[3][3];
	}

	Matrix4 Matrix4::Transposed() const
	{
		Matrix4 r;
		r.m[0][0] = m[0][0]; r.m[1][0] = m[0][1]; r.m[2][0] = m[0][2]; r.m[3][0] = m[0][3];
		r.m[0][1] = m[1][0]; r.m[1][1] = m[1][1]; r.m[2][1] = m[1][2]; r.m[3][1] = m[1][3];
		r.m[0][2] = m[2][0]; r.m[1][2] = m[2][1]; r.m[2][2] = m[2][2]; r.m[3][2] = m[2][3];
		r.m[0][3] = m[3][0]; r.m[1][3] = m[3][1]; r.m[2][3] = m[3][2]; r.m[3][3] = m[3][3];
		return r;
	}

	Matrix4 Matrix4::operator*(float f) const
	{
		Matrix4 r;
		r.m[0][0] *= f;
		r.m[0][1] *= f;
		r.m[0][2] *= f;
		r.m[0][3] *= f;

		r.m[1][0] *= f;
		r.m[1][1] *= f;
		r.m[1][2] *= f;
		r.m[1][3] *= f;

		r.m[2][0] *= f;
		r.m[2][1] *= f;
		r.m[2][2] *= f;
		r.m[2][3] *= f;

		r.m[3][0] *= f;
		r.m[3][1] *= f;
		r.m[3][2] *= f;
		r.m[3][3] *= f;

		return r;
	}

	Matrix4 Matrix4::operator+(const Matrix4& t) const
	{
		Matrix4 r;
		r.m[0][0] = m[0][0] + t.m[0][0];
		r.m[0][1] = m[0][1] + t.m[0][1];
		r.m[0][2] = m[0][2] + t.m[0][2];
		r.m[0][3] = m[0][3] + t.m[0][3];

		r.m[1][0] = m[1][0] + t.m[1][0];
		r.m[1][1] = m[1][1] + t.m[1][1];
		r.m[1][2] = m[1][2] + t.m[1][2];
		r.m[1][3] = m[1][3] + t.m[1][3];

		r.m[2][0] = m[2][0] + t.m[2][0];
		r.m[2][1] = m[2][1] + t.m[2][1];
		r.m[2][2] = m[2][2] + t.m[2][2];
		r.m[2][3] = m[2][3] + t.m[2][3];

		r.m[3][0] = m[3][0] + t.m[3][0];
		r.m[3][1] = m[3][1] + t.m[3][1];
		r.m[3][2] = m[3][2] + t.m[3][2];
		r.m[3][3] = m[3][3] + t.m[3][3];

		return r;
	}

	Matrix4 Matrix4::operator-(const Matrix4& t) const
	{
		Matrix4 r;

		r.m[0][0] = m[0][0] - t.m[0][0];
		r.m[0][1] = m[0][1] - t.m[0][1];
		r.m[0][2] = m[0][2] - t.m[0][2];
		r.m[0][3] = m[0][3] - t.m[0][3];

		r.m[1][0] = m[1][0] - t.m[1][0];
		r.m[1][1] = m[1][1] - t.m[1][1];
		r.m[1][2] = m[1][2] - t.m[1][2];
		r.m[1][3] = m[1][3] - t.m[1][3];

		r.m[2][0] = m[2][0] - t.m[2][0];
		r.m[2][1] = m[2][1] - t.m[2][1];
		r.m[2][2] = m[2][2] - t.m[2][2];
		r.m[2][3] = m[2][3] - t.m[2][3];

		r.m[3][0] = m[3][0] - t.m[3][0];
		r.m[3][1] = m[3][1] - t.m[3][1];
		r.m[3][2] = m[3][2] - t.m[3][2];
		r.m[3][3] = m[3][3] - t.m[3][3];

		return r;
	}

	Matrix4 Matrix4::operator*(const Matrix4& t) const
	{
		Matrix4 r;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				r.m[i][j] = m[0][j] * t.m[i][0] + m[1][j] * t.m[i][1] + m[2][j] * t.m[i][2] + m[3][j] * t.m[i][3];
		}

		return r;
	}

	Matrix4& Matrix4::operator*=(float f)
	{
		m[0][0] *= f;
		m[0][1] *= f;
		m[0][2] *= f;
		m[0][3] *= f;

		m[1][0] *= f;
		m[1][1] *= f;
		m[1][2] *= f;
		m[1][3] *= f;

		m[2][0] *= f;
		m[2][1] *= f;
		m[2][2] *= f;
		m[2][3] *= f;

		m[3][0] *= f;
		m[3][1] *= f;
		m[3][2] *= f;
		m[3][3] *= f;

		return *this;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& t)
	{
		m[0][0] = m[0][0] + t.m[0][0];
		m[0][1] = m[0][1] + t.m[0][1];
		m[0][2] = m[0][2] + t.m[0][2];
		m[0][3] = m[0][3] + t.m[0][3];

		m[1][0] = m[1][0] + t.m[1][0];
		m[1][1] = m[1][1] + t.m[1][1];
		m[1][2] = m[1][2] + t.m[1][2];
		m[1][3] = m[1][3] + t.m[1][3];

		m[2][0] = m[2][0] + t.m[2][0];
		m[2][1] = m[2][1] + t.m[2][1];
		m[2][2] = m[2][2] + t.m[2][2];
		m[2][3] = m[2][3] + t.m[2][3];

		m[3][0] = m[3][0] + t.m[3][0];
		m[3][1] = m[3][1] + t.m[3][1];
		m[3][2] = m[3][2] + t.m[3][2];
		m[3][3] = m[3][3] + t.m[3][3];

		return *this;
	}

	Matrix4& Matrix4::operator-=(const Matrix4& t)
	{
		m[0][0] = m[0][0] - t.m[0][0];
		m[0][1] = m[0][1] - t.m[0][1];
		m[0][2] = m[0][2] - t.m[0][2];
		m[0][3] = m[0][3] - t.m[0][3];

		m[1][0] = m[1][0] - t.m[1][0];
		m[1][1] = m[1][1] - t.m[1][1];
		m[1][2] = m[1][2] - t.m[1][2];
		m[1][3] = m[1][3] - t.m[1][3];

		m[2][0] = m[2][0] - t.m[2][0];
		m[2][1] = m[2][1] - t.m[2][1];
		m[2][2] = m[2][2] - t.m[2][2];
		m[2][3] = m[2][3] - t.m[2][3];

		m[3][0] = m[3][0] - t.m[3][0];
		m[3][1] = m[3][1] - t.m[3][1];
		m[3][2] = m[3][2] - t.m[3][2];
		m[3][3] = m[3][3] - t.m[3][3];

		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& t)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				m[i][j] = m[0][j] * t.m[i][0] + m[1][j] * t.m[i][1] + m[2][j] * t.m[i][2] + m[3][j] * t.m[i][3];
		}

		return *this;
	}

	Vector3 Matrix4::Transform(const Vector3& v) const
	{
		Vector3 vecResult;
		vecResult.x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0];
		vecResult.y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1];
		vecResult.z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2];
		return vecResult;
	}

	Vector3 Matrix4::TransformDirection(const Vector3& v) const
	{
		Vector3 vecResult;
		vecResult.x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
		vecResult.y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
		vecResult.z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
		return vecResult;
	}

	Matrix4 Matrix4::Translation(const Vector3& pos)
	{
		return Matrix4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			pos.x, pos.y, pos.z, 1);
	}

	Matrix4 Matrix4::Translation(float x, float y, float z)
	{
		return Translation(Vector3(x, y, z));
	}

	Matrix4 Matrix4::RotationAxis(const Vector3& axis, float angle)
	{
		const float x = axis.x;
		const float y = axis.y;
		const float z = axis.z;

		const float c = cos(angle* Math::PI/ 180);
		const float s = sin(angle*Math::PI / 180);
		const float t = 1 - c;

		Matrix4 m = Matrix4::IDENTITY;
		m.m[0][0] = x*x*t + c;
		m.m[1][0] = x*y*t - z*s;
		m.m[2][0] = x*z*t + y*s;

		m.m[0][1] = y*x*t + z*s;
		m.m[1][1] = y*y*t + c;
		m.m[2][1] = y*z*t - x*s;

		m.m[0][2] = z*x*t - y*s;
		m.m[1][2] = z*y*t + x*s;
		m.m[2][2] = z*z*t + c;

		return m;
	}

	Matrix4 Matrix4::Scale(const Vector3& scale)
	{
		return Matrix4(
			scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1);
	}

	Matrix4 Matrix4::LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		auto zaxis = (at - eye).Normalized();
		auto xaxis = Vector3::Cross(up, zaxis).Normalized();
		auto yaxis = Vector3::Cross(zaxis, xaxis);
		return Matrix4(
			xaxis.x, yaxis.x, zaxis.x, 0,
			xaxis.y, yaxis.y, zaxis.y, 0,
			xaxis.z, yaxis.z, zaxis.z, 0,
			-xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye), 1);
	}

	Matrix4 Matrix4::OrthoProjection(float width, float height, float znear, float zfar)
	{
		const float zd = zfar - znear;
		return Matrix4(
			2 / width, 0, 0, 0,
			0, 2 / height, 0, 0,
			0, 0, 1 / zd, 0,
			0, 0, -znear / zd, 1);
	}

	Matrix4 Matrix4::OrthoProjection(float l, float r, float b, float t, float znear, float zfar)
	{
		const float zd = zfar - znear;
		return Matrix4(
			2 / (r - l), 0, 0, 0,
			0, 2 / (t - b), 0, 0,
			0, 0, 1 / zd, 0,
			(l + r) / (l - r), (t + b) / (b - t), -znear / zd, 1);
	}

	Matrix4 Matrix4::PerspectiveFovLH(float fovy, float aspect, float znear, float zfar)
	{
		const float zd = zfar - znear;
		const float yScale = Math::Cot(fovy / 2);
		const float xScale = yScale / aspect;
		return Matrix4(
			xScale, 0, 0, 0,
			0, yScale, 0, 0,
			0, 0, zfar / zd, 1,
			0, 0, -znear*zfar / zd, 0);
	}

	Matrix4 Matrix4::PerspectiveLH(float w, float h, float znear, float zfar)
	{
		const float zd = zfar - znear;
		return Matrix4(
			2 * znear / w, 0, 0, 0,
			0, 2 * znear / h, 0, 0,
			0, 0, zfar / zd, 1,
			0, 0, -znear*zfar / zd, 0);
	}
}