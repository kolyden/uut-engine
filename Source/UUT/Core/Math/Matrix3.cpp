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

		val = _m[0 * 3 + 0] * ((_m[1 * 3 + 1] * _m[2 * 3 + 2]) - (_m[2 * 3 + 1] * _m[1 * 3 + 2]));
		val -= _m[0 * 3 + 1] * ((_m[1 * 3 + 0] * _m[2 * 3 + 2]) - (_m[2 * 3 + 0] * _m[1 * 3 + 2]));
		val += _m[0 * 3 + 2] * ((_m[1 * 3 + 0] * _m[2 * 3 + 1]) - (_m[2 * 3 + 0] * _m[1 * 3 + 1]));

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
		_m[0 * 3 + 0] += mat._m[0 * 3 + 0];
		_m[0 * 3 + 1] += mat._m[0 * 3 + 1];
		_m[0 * 3 + 2] += mat._m[0 * 3 + 2];
		_m[1 * 3 + 0] += mat._m[1 * 3 + 0];
		_m[1 * 3 + 1] += mat._m[1 * 3 + 1];
		_m[1 * 3 + 2] += mat._m[1 * 3 + 2];
		_m[2 * 3 + 0] += mat._m[2 * 3 + 0];
		_m[2 * 3 + 1] += mat._m[2 * 3 + 1];
		_m[2 * 3 + 2] += mat._m[2 * 3 + 2];

		return *this;
	}

	Matrix3& Matrix3::Sub(const Matrix3& mat)
	{
		_m[0 * 3 + 0] -= mat._m[0 * 3 + 0];
		_m[0 * 3 + 1] -= mat._m[0 * 3 + 1];
		_m[0 * 3 + 2] -= mat._m[0 * 3 + 2];
		_m[1 * 3 + 0] -= mat._m[1 * 3 + 0];
		_m[1 * 3 + 1] -= mat._m[1 * 3 + 1];
		_m[1 * 3 + 2] -= mat._m[1 * 3 + 2];
		_m[2 * 3 + 0] -= mat._m[2 * 3 + 0];
		_m[2 * 3 + 1] -= mat._m[2 * 3 + 1];
		_m[2 * 3 + 2] -= mat._m[2 * 3 + 2];

		return *this;
	}

	Matrix3& Matrix3::Multiply(const Matrix3& mat)
	{
		Matrix3 result;

		result._m[0] = _m[0] * mat._m[0] + _m[3] * mat._m[1] + _m[6] * mat._m[2];
		result._m[1] = _m[1] * mat._m[0] + _m[4] * mat._m[1] + _m[7] * mat._m[2];
		result._m[2] = _m[2] * mat._m[0] + _m[5] * mat._m[1] + _m[8] * mat._m[2];
		result._m[3] = _m[0] * mat._m[3] + _m[3] * mat._m[4] + _m[6] * mat._m[5];
		result._m[4] = _m[1] * mat._m[3] + _m[4] * mat._m[4] + _m[7] * mat._m[5];
		result._m[5] = _m[2] * mat._m[3] + _m[5] * mat._m[4] + _m[8] * mat._m[5];
		result._m[6] = _m[0] * mat._m[6] + _m[3] * mat._m[7] + _m[6] * mat._m[8];
		result._m[7] = _m[1] * mat._m[6] + _m[4] * mat._m[7] + _m[7] * mat._m[8];
		result._m[8] = _m[2] * mat._m[6] + _m[5] * mat._m[7] + _m[8] * mat._m[8];

		*this = result;
		return *this;
	}

	Matrix3& Matrix3::Divide(const Matrix3& mat)
	{
		Matrix3 result;

		result._m[0] = _m[0] / mat._m[0] + _m[3] / mat._m[1] + _m[6] / mat._m[2];
		result._m[1] = _m[1] / mat._m[0] + _m[4] / mat._m[1] + _m[7] / mat._m[2];
		result._m[2] = _m[2] / mat._m[0] + _m[5] / mat._m[1] + _m[8] / mat._m[2];
		result._m[3] = _m[0] / mat._m[3] + _m[3] / mat._m[4] + _m[6] / mat._m[5];
		result._m[4] = _m[1] / mat._m[3] + _m[4] / mat._m[4] + _m[7] / mat._m[5];
		result._m[5] = _m[2] / mat._m[3] + _m[5] / mat._m[4] + _m[8] / mat._m[5];
		result._m[6] = _m[0] / mat._m[6] + _m[3] / mat._m[7] + _m[6] / mat._m[8];
		result._m[7] = _m[1] / mat._m[6] + _m[4] / mat._m[7] + _m[7] / mat._m[8];
		result._m[8] = _m[2] / mat._m[6] + _m[5] / mat._m[7] + _m[8] / mat._m[8];

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
		_m[0] *= f;
		_m[1] *= f;
		_m[2] *= f;
		_m[3] *= f;
		_m[4] *= f;
		_m[5] *= f;
		_m[6] *= f;
		_m[7] *= f;
		_m[8] *= f;

		return *this;
	}

	Matrix3& Matrix3::Divide(float f)
	{
		_m[0] /= f;
		_m[1] /= f;
		_m[2] /= f;
		_m[3] /= f;
		_m[4] /= f;
		_m[5] /= f;
		_m[6] /= f;
		_m[7] /= f;
		_m[8] /= f;

		return *this;
	}

	bool Matrix3::ToEulerAngles(Radian& xAngle, Radian& yAngle, Radian& zAngle)
	{
		xAngle = -Radian(Math::Asin(m[1][2]));
		if (xAngle < Radian(Math::HALF_PI))
		{
			if (xAngle > Radian(-Math::HALF_PI))
			{
				yAngle = Math::Atan2(m[0][2], m[2][2]);
				zAngle = Math::Atan2(m[1][0], m[1][1]);

				return true;
			}
			else
			{
				// Note: Not an unique solution.
				xAngle = Radian(-Math::HALF_PI);
				yAngle = Math::Atan2(-m[0][1], m[0][0]);
				zAngle = Radian(0.0f);

				return false;
			}
		}
		else
		{
			// Note: Not an unique solution.
			xAngle = Radian(Math::HALF_PI);
			yAngle = Math::Atan2(m[0][1], m[0][0]);
			zAngle = Radian(0.0f);

			return false;
		}
	}

	Matrix3 Matrix3::Inverse(const Matrix3& mat)
	{
		Matrix3 result = Matrix3::Adjoint(mat);
		const float d = 1.0f / mat.Det();
		for (int i = 0; i < 9; i++)
			result._m[i] *= d;

		return result;
	}

	Matrix3	Matrix3::Adjoint(const Matrix3& mat)
	{
		Matrix3 result;
		result._m[0 * 3 + 0] = ((mat._m[1 * 3 + 1] * mat._m[2 * 3 + 2]) - (mat._m[1 * 3 + 2] * mat._m[2 * 3 + 1]));
		result._m[1 * 3 + 0] = -((mat._m[1 * 3 + 0] * mat._m[2 * 3 + 2]) - (mat._m[1 * 3 + 2] * mat._m[2 * 3 + 0]));
		result._m[2 * 3 + 0] = ((mat._m[1 * 3 + 0] * mat._m[2 * 3 + 1]) - (mat._m[1 * 3 + 1] * mat._m[2 * 3 + 0]));
		result._m[0 * 3 + 1] = -((mat._m[0 * 3 + 1] * mat._m[2 * 3 + 2]) - (mat._m[0 * 3 + 2] * mat._m[2 * 3 + 1]));
		result._m[1 * 3 + 1] = ((mat._m[0 * 3 + 0] * mat._m[2 * 3 + 2]) - (mat._m[0 * 3 + 2] * mat._m[2 * 3 + 0]));
		result._m[2 * 3 + 1] = -((mat._m[0 * 3 + 0] * mat._m[2 * 3 + 1]) - (mat._m[0 * 3 + 1] * mat._m[2 * 3 + 0]));
		result._m[0 * 3 + 2] = ((mat._m[0 * 3 + 1] * mat._m[1 * 3 + 2]) - (mat._m[0 * 3 + 2] * mat._m[1 * 3 + 1]));
		result._m[1 * 3 + 2] = -((mat._m[0 * 3 + 0] * mat._m[1 * 3 + 2]) - (mat._m[0 * 3 + 2] * mat._m[1 * 3 + 0]));
		result._m[2 * 3 + 2] = ((mat._m[0 * 3 + 0] * mat._m[1 * 3 + 1]) - (mat._m[0 * 3 + 1] * mat._m[1 * 3 + 0]));
		return result;
	}

	Matrix3 Matrix3::Orthonormalize(const Matrix3& mat)
	{
		Vector3 c[3];

		for (int i = 0; i < 3; i++)
			c[i] = Vector3(mat._m[i * 3 + 0], mat._m[i * 3 + 1], mat._m[i * 3 + 2]);

		c[0].Normalize();
		c[2] = Vector3::Cross(c[0], c[1]).Normalized();
		c[1] = Vector3::Cross(c[2], c[0]).Normalized();

		Matrix3 m;
		for (int i = 0; i < 3; i++)
		{
			m._m[i * 3 + 0] = c[i].x;
			m._m[i * 3 + 1] = c[i].y;
			m._m[i * 3 + 2] = c[i].z;
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
		return RotateRad(Math::DEG2RAD * rot);
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
		const float rot = Math::DEG2RAD *angleDeg;
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