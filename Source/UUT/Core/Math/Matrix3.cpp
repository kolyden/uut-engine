#include "Matrix3.h"
#include <cstring>
#include "Vector3.h"
#include "Math.h"
#include "Matrix4.h"

namespace uut
{
	const Matrix3 Matrix3::ZERO(
		0, 0, 0,
		0, 0, 0,
		0, 0, 0);
	const Matrix3 Matrix3::IDENTITY(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);

	Matrix3::Matrix3(
		float _m00, float _m01, float _m02,
		float _m10, float _m11, float _m12,
		float _m20, float _m21, float _m22)
		: m00(_m00), m01(_m01), m02(_m02)
		, m10(_m10), m11(_m11), m12(_m12)
		, m20(_m20), m21(_m21), m22(_m22)
	{
	}

	void Matrix3::MakeZero()
	{
		memset(m, 0, sizeof(float) * 9);
	}

	void Matrix3::MakeIdentity()
	{
		m01 = m02 = m10 = m12 = m20 = m21 = 0;
		m00 = m11 = m22 = 1;
	}

	void Matrix3::operator=(const Matrix3& mat)
	{
		memcpy(m, mat.m, sizeof(m));
	}

	bool Matrix3::IsZero() const
	{
		return IsEqual(ZERO);
	}

	bool Matrix3::IsIdentity() const
	{
		return IsEqual(IDENTITY);
	}

	float Matrix3::Det() const
	{
		float val;

		val = m[0 * 3 + 0] * ((m[1 * 3 + 1] * m[2 * 3 + 2]) - (m[2 * 3 + 1] * m[1 * 3 + 2]));
		val -= m[0 * 3 + 1] * ((m[1 * 3 + 0] * m[2 * 3 + 2]) - (m[2 * 3 + 0] * m[1 * 3 + 2]));
		val += m[0 * 3 + 2] * ((m[1 * 3 + 0] * m[2 * 3 + 1]) - (m[2 * 3 + 0] * m[1 * 3 + 1]));

		return val;
	}

	Matrix3& Matrix3::Inverse()
	{
		*this = Inverse(*this);
		return *this;
	}

	Matrix3& Matrix3::Adjoint()
	{
		*this = Adjoint(*this);
		return *this;
	}

	bool Matrix3::IsEqual(const Matrix3& mat) const
	{
		return (
			m00 == mat.m00 && m01 == mat.m01 && m02 == mat.m02 &&
			m10 == mat.m10 && m11 == mat.m11 && m12 == mat.m12 &&
			m20 == mat.m20 && m21 == mat.m21 && m22 == mat.m22);
	}

	Matrix3& Matrix3::Add(const Matrix3& mat)
	{
		m[0 * 3 + 0] += mat.m[0 * 3 + 0];
		m[0 * 3 + 1] += mat.m[0 * 3 + 1];
		m[0 * 3 + 2] += mat.m[0 * 3 + 2];
		m[1 * 3 + 0] += mat.m[1 * 3 + 0];
		m[1 * 3 + 1] += mat.m[1 * 3 + 1];
		m[1 * 3 + 2] += mat.m[1 * 3 + 2];
		m[2 * 3 + 0] += mat.m[2 * 3 + 0];
		m[2 * 3 + 1] += mat.m[2 * 3 + 1];
		m[2 * 3 + 2] += mat.m[2 * 3 + 2];

		return *this;
	}

	Matrix3& Matrix3::Sub(const Matrix3& mat)
	{
		m[0 * 3 + 0] -= mat.m[0 * 3 + 0];
		m[0 * 3 + 1] -= mat.m[0 * 3 + 1];
		m[0 * 3 + 2] -= mat.m[0 * 3 + 2];
		m[1 * 3 + 0] -= mat.m[1 * 3 + 0];
		m[1 * 3 + 1] -= mat.m[1 * 3 + 1];
		m[1 * 3 + 2] -= mat.m[1 * 3 + 2];
		m[2 * 3 + 0] -= mat.m[2 * 3 + 0];
		m[2 * 3 + 1] -= mat.m[2 * 3 + 1];
		m[2 * 3 + 2] -= mat.m[2 * 3 + 2];

		return *this;
	}

	Matrix3& Matrix3::Multiply(const Matrix3& mat)
	{
		Matrix3 result;

		result.m[0] = m[0] * mat.m[0] + m[3] * mat.m[1] + m[6] * mat.m[2];
		result.m[1] = m[1] * mat.m[0] + m[4] * mat.m[1] + m[7] * mat.m[2];
		result.m[2] = m[2] * mat.m[0] + m[5] * mat.m[1] + m[8] * mat.m[2];
		result.m[3] = m[0] * mat.m[3] + m[3] * mat.m[4] + m[6] * mat.m[5];
		result.m[4] = m[1] * mat.m[3] + m[4] * mat.m[4] + m[7] * mat.m[5];
		result.m[5] = m[2] * mat.m[3] + m[5] * mat.m[4] + m[8] * mat.m[5];
		result.m[6] = m[0] * mat.m[6] + m[3] * mat.m[7] + m[6] * mat.m[8];
		result.m[7] = m[1] * mat.m[6] + m[4] * mat.m[7] + m[7] * mat.m[8];
		result.m[8] = m[2] * mat.m[6] + m[5] * mat.m[7] + m[8] * mat.m[8];

		*this = result;
		return *this;
	}

	Matrix3& Matrix3::Divide(const Matrix3& mat)
	{
		Matrix3 result;

		result.m[0] = m[0] / mat.m[0] + m[3] / mat.m[1] + m[6] / mat.m[2];
		result.m[1] = m[1] / mat.m[0] + m[4] / mat.m[1] + m[7] / mat.m[2];
		result.m[2] = m[2] / mat.m[0] + m[5] / mat.m[1] + m[8] / mat.m[2];
		result.m[3] = m[0] / mat.m[3] + m[3] / mat.m[4] + m[6] / mat.m[5];
		result.m[4] = m[1] / mat.m[3] + m[4] / mat.m[4] + m[7] / mat.m[5];
		result.m[5] = m[2] / mat.m[3] + m[5] / mat.m[4] + m[8] / mat.m[5];
		result.m[6] = m[0] / mat.m[6] + m[3] / mat.m[7] + m[6] / mat.m[8];
		result.m[7] = m[1] / mat.m[6] + m[4] / mat.m[7] + m[7] / mat.m[8];
		result.m[8] = m[2] / mat.m[6] + m[5] / mat.m[7] + m[8] / mat.m[8];

		*this = result;
		return *this;
	}

	Vector2 Matrix3::Multiply(const Vector2& vec)
	{
		return Vector2(
			m00*vec.x + m01*vec.y + m02,
			m10*vec.x + m11*vec.y + m12);
	}

	Vector2 Matrix3::Divide(const Vector2& vec)
	{
		return Vector2(
			m00 / vec.x + m01 / vec.y + m02,
			m10 / vec.x + m11 / vec.y + m12);
	}

	Matrix3& Matrix3::Multiply(float f)
	{
		m[0] *= f;
		m[1] *= f;
		m[2] *= f;
		m[3] *= f;
		m[4] *= f;
		m[5] *= f;
		m[6] *= f;
		m[7] *= f;
		m[8] *= f;

		return *this;
	}

	Matrix3& Matrix3::Divide(float f)
	{
		m[0] /= f;
		m[1] /= f;
		m[2] /= f;
		m[3] /= f;
		m[4] /= f;
		m[5] /= f;
		m[6] /= f;
		m[7] /= f;
		m[8] /= f;

		return *this;
	}

	Matrix4 Matrix3::ToMat4() const
	{
		return Matrix4(
			m00, m10, m20, 0.0f,
			m01, m11, m21, 0.0f,
			m02, m12, m22, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix3 Matrix3::Inverse(const Matrix3& mat)
	{
		Matrix3 result = Matrix3::Adjoint(mat);
		const float d = 1.0f / mat.Det();
		for (int i = 0; i < 9; i++)
			result.m[i] *= d;

		return result;
	}

	Matrix3	Matrix3::Adjoint(const Matrix3& mat)
	{
		Matrix3 result;
		result.m[0 * 3 + 0] = ((mat.m[1 * 3 + 1] * mat.m[2 * 3 + 2]) - (mat.m[1 * 3 + 2] * mat.m[2 * 3 + 1]));
		result.m[1 * 3 + 0] = -((mat.m[1 * 3 + 0] * mat.m[2 * 3 + 2]) - (mat.m[1 * 3 + 2] * mat.m[2 * 3 + 0]));
		result.m[2 * 3 + 0] = ((mat.m[1 * 3 + 0] * mat.m[2 * 3 + 1]) - (mat.m[1 * 3 + 1] * mat.m[2 * 3 + 0]));
		result.m[0 * 3 + 1] = -((mat.m[0 * 3 + 1] * mat.m[2 * 3 + 2]) - (mat.m[0 * 3 + 2] * mat.m[2 * 3 + 1]));
		result.m[1 * 3 + 1] = ((mat.m[0 * 3 + 0] * mat.m[2 * 3 + 2]) - (mat.m[0 * 3 + 2] * mat.m[2 * 3 + 0]));
		result.m[2 * 3 + 1] = -((mat.m[0 * 3 + 0] * mat.m[2 * 3 + 1]) - (mat.m[0 * 3 + 1] * mat.m[2 * 3 + 0]));
		result.m[0 * 3 + 2] = ((mat.m[0 * 3 + 1] * mat.m[1 * 3 + 2]) - (mat.m[0 * 3 + 2] * mat.m[1 * 3 + 1]));
		result.m[1 * 3 + 2] = -((mat.m[0 * 3 + 0] * mat.m[1 * 3 + 2]) - (mat.m[0 * 3 + 2] * mat.m[1 * 3 + 0]));
		result.m[2 * 3 + 2] = ((mat.m[0 * 3 + 0] * mat.m[1 * 3 + 1]) - (mat.m[0 * 3 + 1] * mat.m[1 * 3 + 0]));
		return result;
	}

	Matrix3 Matrix3::Orthonormalize(const Matrix3& mat)
	{
		Vector3 c[3];

		for (int i = 0; i < 3; i++)
			c[i] = Vector3(mat.m[i * 3 + 0], mat.m[i * 3 + 1], mat.m[i * 3 + 2]);

		c[0].Normalize();
		c[2] = c[0].Cross(c[1]).Normalized();
		c[1] = c[2].Cross(c[0]).Normalized();

		Matrix3 m;
		for (int i = 0; i < 3; i++)
		{
			m.m[i * 3 + 0] = c[i].x;
			m.m[i * 3 + 1] = c[i].y;
			m.m[i * 3 + 2] = c[i].z;
		}
		return mat;
	}

	Matrix3	Matrix3::Transpose(const Matrix3& mat)
	{
		return Matrix3(
			mat.m00, mat.m10, mat.m20,
			mat.m01, mat.m11, mat.m21,
			mat.m02, mat.m12, mat.m22);
	}

	Matrix3	Matrix3::Translate(const Vector2& pos)
	{
		Matrix3 mat = IDENTITY;
		mat.m02 = pos.x;
		mat.m12 = pos.y;
		return mat;
	}

	Matrix3	Matrix3::Translate(float dx, float dy)
	{
		Matrix3 mat = IDENTITY;
		mat.m02 = dx;
		mat.m12 = dy;
		return mat;
	}

	Matrix3	Matrix3::RotateRad(float rot)
	{
		Matrix3 mat = IDENTITY;

		const float sinRot = -Math::Sin(rot);
		const float cosRot = Math::Cos(rot);

		mat.m00 = cosRot;
		mat.m01 = -sinRot;
		mat.m10 = sinRot;
		mat.m11 = cosRot;

		return mat;
	}

	Matrix3	Matrix3::RotateDeg(float rot)
	{
		return RotateRad(Math::Deg2Rad * rot);
	}

	Matrix3	Matrix3::Scale(const Vector2& scale)
	{
		Matrix3 mat = IDENTITY;
		mat.m00 = scale.x;
		mat.m11 = scale.y;
		return mat;
	}

	Matrix3	Matrix3::Scale(float scale)
	{
		Matrix3 mat = IDENTITY;
		mat.m00 = scale;
		mat.m11 = scale;
		return mat;
	}

	Matrix3	Matrix3::Scale(float scalex, float scaley)
	{
		Matrix3 mat = IDENTITY;
		mat.m00 = scalex;
		mat.m11 = scaley;
		return mat;
	}

	Matrix3	Matrix3::Transform(const Vector2& pos, float angleDeg, const Vector2& scale)
	{
		const float rot = Math::Deg2Rad *angleDeg;
		const float sinRot = -Math::Sin(rot);
		const float cosRot = Math::Cos(rot);

		return Matrix3(
			scale.x * cosRot, scale.y * (-sinRot), pos.x,
			scale.x * sinRot, scale.y * cosRot, pos.y,
			0, 0, 1);
	}

	Matrix3	Matrix3::Transform(const Vector2& translate, float angleDeg, float scale)
	{
		return Transform(translate, angleDeg, Vector2(scale));
	}
}
