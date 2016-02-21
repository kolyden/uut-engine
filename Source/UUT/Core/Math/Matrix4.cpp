#include "Matrix4.h"
#include "Vector3.h"
#include "Math.h"
#include <cstring>
#include "Quaternion.h"

namespace uut
{
	const Matrix4 Matrix4::ZERO(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);

	const Matrix4 Matrix4::IDENTITY(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Matrix4::Matrix4(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33)
		: m00(_m00), m01(_m01), m02(_m02), m03(_m03)
		, m10(_m10), m11(_m11), m12(_m12), m13(_m13)
		, m20(_m20), m21(_m21), m22(_m22), m23(_m23)
		, m30(_m30), m31(_m31), m32(_m32), m33(_m33)
	{
	}

	void Matrix4::MakeZero()
	{
		memset(m, 0, sizeof(float) * 16);
	}

	void Matrix4::MakeIdentity()
	{
		MakeZero();
		m00 = m11 = m22 = m33 = 1;
	}

	bool Matrix4::IsZero() const
	{
		return IsEqual(ZERO);
	}

	bool Matrix4::IsIdentity() const
	{
		return IsEqual(IDENTITY);
	}

	float Matrix4::Det() const
	{
		return (mtx[0][0] * mtx[1][1] - mtx[1][0] * mtx[0][1])* (mtx[2][2] * mtx[3][3] - mtx[3][2] * mtx[2][3]) -
			(mtx[0][0] * mtx[2][1] - mtx[2][0] * mtx[0][1]) * (mtx[1][2] * mtx[3][3] - mtx[3][2] * mtx[1][3]) +
			(mtx[0][0] * mtx[3][1] - mtx[3][0] * mtx[0][1])* (mtx[1][2] * mtx[2][3] - mtx[2][2] * mtx[1][3]) +
			(mtx[1][0] * mtx[2][1] - mtx[2][0] * mtx[1][1])* (mtx[0][2] * mtx[3][3] - mtx[3][2] * mtx[0][3]) -
			(mtx[1][0] * mtx[3][1] - mtx[3][0] * mtx[1][1])* (mtx[0][2] * mtx[2][3] - mtx[2][2] * mtx[0][3]) +
			(mtx[2][0] * mtx[3][1] - mtx[3][0] * mtx[2][1])* (mtx[0][2] * mtx[1][3] - mtx[1][2] * mtx[0][3]);
	}

	Matrix4& Matrix4::Inverse()
	{
		*this = Inverse(*this);
		return *this;
	}

	bool Matrix4::IsEqual(const Matrix4& rhs) const
	{
		return Math::Approximately(mtx[0][0], rhs.mtx[0][0])
			&& Math::Approximately(mtx[0][1], rhs.mtx[0][1])
			&& Math::Approximately(mtx[0][2], rhs.mtx[0][2])
			&& Math::Approximately(mtx[0][3], rhs.mtx[0][3])
			&& Math::Approximately(mtx[1][0], rhs.mtx[1][0])
			&& Math::Approximately(mtx[1][1], rhs.mtx[1][1])
			&& Math::Approximately(mtx[1][2], rhs.mtx[1][2])
			&& Math::Approximately(mtx[1][3], rhs.mtx[1][3])
			&& Math::Approximately(mtx[2][0], rhs.mtx[2][0])
			&& Math::Approximately(mtx[2][1], rhs.mtx[2][1])
			&& Math::Approximately(mtx[2][2], rhs.mtx[2][2])
			&& Math::Approximately(mtx[2][3], rhs.mtx[2][3])
			&& Math::Approximately(mtx[3][0], rhs.mtx[3][0])
			&& Math::Approximately(mtx[3][1], rhs.mtx[3][1])
			&& Math::Approximately(mtx[3][2], rhs.mtx[3][2])
			&& Math::Approximately(mtx[3][3], rhs.mtx[3][3]);
	}

	Matrix4& Matrix4::Add(const Matrix4& rhs)
	{
		mtx[0][0] += rhs.mtx[0][0], mtx[0][1] += rhs.mtx[0][1], mtx[0][2] += rhs.mtx[0][2], mtx[0][3] += rhs.mtx[0][3];
		mtx[1][0] += rhs.mtx[1][0], mtx[1][1] += rhs.mtx[1][1], mtx[1][2] += rhs.mtx[1][2], mtx[1][3] += rhs.mtx[1][3];
		mtx[2][0] += rhs.mtx[2][0], mtx[2][1] += rhs.mtx[2][1], mtx[2][2] += rhs.mtx[2][2], mtx[2][3] += rhs.mtx[2][3];
		mtx[3][0] += rhs.mtx[3][0], mtx[3][1] += rhs.mtx[3][1], mtx[3][2] += rhs.mtx[3][2], mtx[3][3] += rhs.mtx[3][3];
		return *this;
	}

	Matrix4& Matrix4::Sub(const Matrix4& rhs)
	{
		mtx[0][0] -= rhs.mtx[0][0], mtx[0][1] -= rhs.mtx[0][1], mtx[0][2] -= rhs.mtx[0][2], mtx[0][3] -= rhs.mtx[0][3];
		mtx[1][0] -= rhs.mtx[1][0], mtx[1][1] -= rhs.mtx[1][1], mtx[1][2] -= rhs.mtx[1][2], mtx[1][3] -= rhs.mtx[1][3];
		mtx[2][0] -= rhs.mtx[2][0], mtx[2][1] -= rhs.mtx[2][1], mtx[2][2] -= rhs.mtx[2][2], mtx[2][3] -= rhs.mtx[2][3];
		mtx[3][0] -= rhs.mtx[3][0], mtx[3][1] -= rhs.mtx[3][1], mtx[3][2] -= rhs.mtx[3][2], mtx[3][3] -= rhs.mtx[3][3];
		return *this;
	}

	Matrix4& Matrix4::Multiply(const Matrix4& rhs)
	{
		Matrix4 tmp;

		// Row 1.
		tmp.mtx[0][0] = (mtx[0][0] * rhs.mtx[0][0]) + (mtx[0][1] * rhs.mtx[1][0]) + (mtx[0][2] * rhs.mtx[2][0]) + (mtx[0][3] * rhs.mtx[3][0]);
		tmp.mtx[0][1] = (mtx[0][0] * rhs.mtx[0][1]) + (mtx[0][1] * rhs.mtx[1][1]) + (mtx[0][2] * rhs.mtx[2][1]) + (mtx[0][3] * rhs.mtx[3][1]);
		tmp.mtx[0][2] = (mtx[0][0] * rhs.mtx[0][2]) + (mtx[0][1] * rhs.mtx[1][2]) + (mtx[0][2] * rhs.mtx[2][2]) + (mtx[0][3] * rhs.mtx[3][2]);
		tmp.mtx[0][3] = (mtx[0][0] * rhs.mtx[0][3]) + (mtx[0][1] * rhs.mtx[1][3]) + (mtx[0][2] * rhs.mtx[2][3]) + (mtx[0][3] * rhs.mtx[3][3]);

		// Row 2.
		tmp.mtx[1][0] = (mtx[1][0] * rhs.mtx[0][0]) + (mtx[1][1] * rhs.mtx[1][0]) + (mtx[1][2] * rhs.mtx[2][0]) + (mtx[1][3] * rhs.mtx[3][0]);
		tmp.mtx[1][1] = (mtx[1][0] * rhs.mtx[0][1]) + (mtx[1][1] * rhs.mtx[1][1]) + (mtx[1][2] * rhs.mtx[2][1]) + (mtx[1][3] * rhs.mtx[3][1]);
		tmp.mtx[1][2] = (mtx[1][0] * rhs.mtx[0][2]) + (mtx[1][1] * rhs.mtx[1][2]) + (mtx[1][2] * rhs.mtx[2][2]) + (mtx[1][3] * rhs.mtx[3][2]);
		tmp.mtx[1][3] = (mtx[1][0] * rhs.mtx[0][3]) + (mtx[1][1] * rhs.mtx[1][3]) + (mtx[1][2] * rhs.mtx[2][3]) + (mtx[1][3] * rhs.mtx[3][3]);

		// Row 3.
		tmp.mtx[2][0] = (mtx[2][0] * rhs.mtx[0][0]) + (mtx[2][1] * rhs.mtx[1][0]) + (mtx[2][2] * rhs.mtx[2][0]) + (mtx[2][3] * rhs.mtx[3][0]);
		tmp.mtx[2][1] = (mtx[2][0] * rhs.mtx[0][1]) + (mtx[2][1] * rhs.mtx[1][1]) + (mtx[2][2] * rhs.mtx[2][1]) + (mtx[2][3] * rhs.mtx[3][1]);
		tmp.mtx[2][2] = (mtx[2][0] * rhs.mtx[0][2]) + (mtx[2][1] * rhs.mtx[1][2]) + (mtx[2][2] * rhs.mtx[2][2]) + (mtx[2][3] * rhs.mtx[3][2]);
		tmp.mtx[2][3] = (mtx[2][0] * rhs.mtx[0][3]) + (mtx[2][1] * rhs.mtx[1][3]) + (mtx[2][2] * rhs.mtx[2][3]) + (mtx[2][3] * rhs.mtx[3][3]);

		// Row 4.
		tmp.mtx[3][0] = (mtx[3][0] * rhs.mtx[0][0]) + (mtx[3][1] * rhs.mtx[1][0]) + (mtx[3][2] * rhs.mtx[2][0]) + (mtx[3][3] * rhs.mtx[3][0]);
		tmp.mtx[3][1] = (mtx[3][0] * rhs.mtx[0][1]) + (mtx[3][1] * rhs.mtx[1][1]) + (mtx[3][2] * rhs.mtx[2][1]) + (mtx[3][3] * rhs.mtx[3][1]);
		tmp.mtx[3][2] = (mtx[3][0] * rhs.mtx[0][2]) + (mtx[3][1] * rhs.mtx[1][2]) + (mtx[3][2] * rhs.mtx[2][2]) + (mtx[3][3] * rhs.mtx[3][2]);
		tmp.mtx[3][3] = (mtx[3][0] * rhs.mtx[0][3]) + (mtx[3][1] * rhs.mtx[1][3]) + (mtx[3][2] * rhs.mtx[2][3]) + (mtx[3][3] * rhs.mtx[3][3]);

		*this = tmp;
		return *this;
	}

	Vector3 Matrix4::Multiply(const Vector3& vec)
	{
		return Vector3(
			(vec.x * mtx[0][0]) + (vec.y * mtx[1][0]) + (vec.z * mtx[2][0]),
			(vec.x * mtx[0][1]) + (vec.y * mtx[1][1]) + (vec.z * mtx[2][1]),
			(vec.x * mtx[0][2]) + (vec.y * mtx[1][2]) + (vec.z * mtx[2][2]));
	}

	Matrix4& Matrix4::Multiply(float scalar)
	{
		mtx[0][0] *= scalar, mtx[0][1] *= scalar, mtx[0][2] *= scalar, mtx[0][3] *= scalar;
		mtx[1][0] *= scalar, mtx[1][1] *= scalar, mtx[1][2] *= scalar, mtx[1][3] *= scalar;
		mtx[2][0] *= scalar, mtx[2][1] *= scalar, mtx[2][2] *= scalar, mtx[2][3] *= scalar;
		mtx[3][0] *= scalar, mtx[3][1] *= scalar, mtx[3][2] *= scalar, mtx[3][3] *= scalar;
		return *this;
	}

	Matrix4& Matrix4::Divide(float scalar)
	{
		mtx[0][0] /= scalar, mtx[0][1] /= scalar, mtx[0][2] /= scalar, mtx[0][3] /= scalar;
		mtx[1][0] /= scalar, mtx[1][1] /= scalar, mtx[1][2] /= scalar, mtx[1][3] /= scalar;
		mtx[2][0] /= scalar, mtx[2][1] /= scalar, mtx[2][2] /= scalar, mtx[2][3] /= scalar;
		mtx[3][0] /= scalar, mtx[3][1] /= scalar, mtx[3][2] /= scalar, mtx[3][3] /= scalar;
		return *this;
	}

	Matrix4 Matrix4::Inverse(const Matrix4& mat)
	{
		Matrix4 tmp;
		float d = mat.Det();

		if (Math::Approximately(d, 0.0f))
		{
			tmp.MakeIdentity();
		}
		else
		{
			d = 1.0f / d;

			tmp.mtx[0][0] = d * (mat.mtx[1][1] * (mat.mtx[2][2] * mat.mtx[3][3] - mat.mtx[3][2] * mat.mtx[2][3]) + mat.mtx[2][1] * (mat.mtx[3][2] * mat.mtx[1][3] - mat.mtx[1][2] * mat.mtx[3][3]) + mat.mtx[3][1] * (mat.mtx[1][2] * mat.mtx[2][3] - mat.mtx[2][2] * mat.mtx[1][3]));
			tmp.mtx[1][0] = d * (mat.mtx[1][2] * (mat.mtx[2][0] * mat.mtx[3][3] - mat.mtx[3][0] * mat.mtx[2][3]) + mat.mtx[2][2] * (mat.mtx[3][0] * mat.mtx[1][3] - mat.mtx[1][0] * mat.mtx[3][3]) + mat.mtx[3][2] * (mat.mtx[1][0] * mat.mtx[2][3] - mat.mtx[2][0] * mat.mtx[1][3]));
			tmp.mtx[2][0] = d * (mat.mtx[1][3] * (mat.mtx[2][0] * mat.mtx[3][1] - mat.mtx[3][0] * mat.mtx[2][1]) + mat.mtx[2][3] * (mat.mtx[3][0] * mat.mtx[1][1] - mat.mtx[1][0] * mat.mtx[3][1]) + mat.mtx[3][3] * (mat.mtx[1][0] * mat.mtx[2][1] - mat.mtx[2][0] * mat.mtx[1][1]));
			tmp.mtx[3][0] = d * (mat.mtx[1][0] * (mat.mtx[3][1] * mat.mtx[2][2] - mat.mtx[2][1] * mat.mtx[3][2]) + mat.mtx[2][0] * (mat.mtx[1][1] * mat.mtx[3][2] - mat.mtx[3][1] * mat.mtx[1][2]) + mat.mtx[3][0] * (mat.mtx[2][1] * mat.mtx[1][2] - mat.mtx[1][1] * mat.mtx[2][2]));

			tmp.mtx[0][1] = d * (mat.mtx[2][1] * (mat.mtx[0][2] * mat.mtx[3][3] - mat.mtx[3][2] * mat.mtx[0][3]) + mat.mtx[3][1] * (mat.mtx[2][2] * mat.mtx[0][3] - mat.mtx[0][2] * mat.mtx[2][3]) + mat.mtx[0][1] * (mat.mtx[3][2] * mat.mtx[2][3] - mat.mtx[2][2] * mat.mtx[3][3]));
			tmp.mtx[1][1] = d * (mat.mtx[2][2] * (mat.mtx[0][0] * mat.mtx[3][3] - mat.mtx[3][0] * mat.mtx[0][3]) + mat.mtx[3][2] * (mat.mtx[2][0] * mat.mtx[0][3] - mat.mtx[0][0] * mat.mtx[2][3]) + mat.mtx[0][2] * (mat.mtx[3][0] * mat.mtx[2][3] - mat.mtx[2][0] * mat.mtx[3][3]));
			tmp.mtx[2][1] = d * (mat.mtx[2][3] * (mat.mtx[0][0] * mat.mtx[3][1] - mat.mtx[3][0] * mat.mtx[0][1]) + mat.mtx[3][3] * (mat.mtx[2][0] * mat.mtx[0][1] - mat.mtx[0][0] * mat.mtx[2][1]) + mat.mtx[0][3] * (mat.mtx[3][0] * mat.mtx[2][1] - mat.mtx[2][0] * mat.mtx[3][1]));
			tmp.mtx[3][1] = d * (mat.mtx[2][0] * (mat.mtx[3][1] * mat.mtx[0][2] - mat.mtx[0][1] * mat.mtx[3][2]) + mat.mtx[3][0] * (mat.mtx[0][1] * mat.mtx[2][2] - mat.mtx[2][1] * mat.mtx[0][2]) + mat.mtx[0][0] * (mat.mtx[2][1] * mat.mtx[3][2] - mat.mtx[3][1] * mat.mtx[2][2]));

			tmp.mtx[0][2] = d * (mat.mtx[3][1] * (mat.mtx[0][2] * mat.mtx[1][3] - mat.mtx[1][2] * mat.mtx[0][3]) + mat.mtx[0][1] * (mat.mtx[1][2] * mat.mtx[3][3] - mat.mtx[3][2] * mat.mtx[1][3]) + mat.mtx[1][1] * (mat.mtx[3][2] * mat.mtx[0][3] - mat.mtx[0][2] * mat.mtx[3][3]));
			tmp.mtx[1][2] = d * (mat.mtx[3][2] * (mat.mtx[0][0] * mat.mtx[1][3] - mat.mtx[1][0] * mat.mtx[0][3]) + mat.mtx[0][2] * (mat.mtx[1][0] * mat.mtx[3][3] - mat.mtx[3][0] * mat.mtx[1][3]) + mat.mtx[1][2] * (mat.mtx[3][0] * mat.mtx[0][3] - mat.mtx[0][0] * mat.mtx[3][3]));
			tmp.mtx[2][2] = d * (mat.mtx[3][3] * (mat.mtx[0][0] * mat.mtx[1][1] - mat.mtx[1][0] * mat.mtx[0][1]) + mat.mtx[0][3] * (mat.mtx[1][0] * mat.mtx[3][1] - mat.mtx[3][0] * mat.mtx[1][1]) + mat.mtx[1][3] * (mat.mtx[3][0] * mat.mtx[0][1] - mat.mtx[0][0] * mat.mtx[3][1]));
			tmp.mtx[3][2] = d * (mat.mtx[3][0] * (mat.mtx[1][1] * mat.mtx[0][2] - mat.mtx[0][1] * mat.mtx[1][2]) + mat.mtx[0][0] * (mat.mtx[3][1] * mat.mtx[1][2] - mat.mtx[1][1] * mat.mtx[3][2]) + mat.mtx[1][0] * (mat.mtx[0][1] * mat.mtx[3][2] - mat.mtx[3][1] * mat.mtx[0][2]));

			tmp.mtx[0][3] = d * (mat.mtx[0][1] * (mat.mtx[2][2] * mat.mtx[1][3] - mat.mtx[1][2] * mat.mtx[2][3]) + mat.mtx[1][1] * (mat.mtx[0][2] * mat.mtx[2][3] - mat.mtx[2][2] * mat.mtx[0][3]) + mat.mtx[2][1] * (mat.mtx[1][2] * mat.mtx[0][3] - mat.mtx[0][2] * mat.mtx[1][3]));
			tmp.mtx[1][3] = d * (mat.mtx[0][2] * (mat.mtx[2][0] * mat.mtx[1][3] - mat.mtx[1][0] * mat.mtx[2][3]) + mat.mtx[1][2] * (mat.mtx[0][0] * mat.mtx[2][3] - mat.mtx[2][0] * mat.mtx[0][3]) + mat.mtx[2][2] * (mat.mtx[1][0] * mat.mtx[0][3] - mat.mtx[0][0] * mat.mtx[1][3]));
			tmp.mtx[2][3] = d * (mat.mtx[0][3] * (mat.mtx[2][0] * mat.mtx[1][1] - mat.mtx[1][0] * mat.mtx[2][1]) + mat.mtx[1][3] * (mat.mtx[0][0] * mat.mtx[2][1] - mat.mtx[2][0] * mat.mtx[0][1]) + mat.mtx[2][3] * (mat.mtx[1][0] * mat.mtx[0][1] - mat.mtx[0][0] * mat.mtx[1][1]));
			tmp.mtx[3][3] = d * (mat.mtx[0][0] * (mat.mtx[1][1] * mat.mtx[2][2] - mat.mtx[2][1] * mat.mtx[1][2]) + mat.mtx[1][0] * (mat.mtx[2][1] * mat.mtx[0][2] - mat.mtx[0][1] * mat.mtx[2][2]) + mat.mtx[2][0] * (mat.mtx[0][1] * mat.mtx[1][2] - mat.mtx[1][1] * mat.mtx[0][2]));
		}

		return tmp;
	}

	Matrix4	Matrix4::Transpose(const Matrix4& mat)
	{
		return Matrix4(
			mat.m00, mat.m10, mat.m20, mat.m30,
			mat.m01, mat.m11, mat.m21, mat.m31,
			mat.m02, mat.m12, mat.m22, mat.m32,
			mat.m03, mat.m13, mat.m23, mat.m33);
	}

	Matrix4	Matrix4::Translate(const Vector3& pos)
	{
		Matrix4 tmp;
		tmp.mtx[0][0] = 1.0f, tmp.mtx[0][1] = 0.0f, tmp.mtx[0][2] = 0.0f, tmp.mtx[0][3] = 0.0f;
		tmp.mtx[1][0] = 0.0f, tmp.mtx[1][1] = 1.0f, tmp.mtx[1][2] = 0.0f, tmp.mtx[1][3] = 0.0f;
		tmp.mtx[2][0] = 0.0f, tmp.mtx[2][1] = 0.0f, tmp.mtx[2][2] = 1.0f, tmp.mtx[2][3] = 0.0f;
		tmp.mtx[3][0] = pos.x, tmp.mtx[3][1] = pos.y, tmp.mtx[3][2] = pos.z, tmp.mtx[3][3] = 1.0f;
		return tmp;
	}

	Matrix4	Matrix4::Translate(float dx, float dy, float dz)
	{
		return Translate(Vector3(dx, dy, dz));
	}

	Matrix4	Matrix4::RotateRad(const Vector3& axis, float angle)
	{
		Matrix4 tmp;

		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		float c = Math::Cos(angle);
		float s = Math::Sin(angle);

		tmp.mtx[0][0] = (x * x) * (1.0f - c) + c;
		tmp.mtx[0][1] = (x * y) * (1.0f - c) + (z * s);
		tmp.mtx[0][2] = (x * z) * (1.0f - c) - (y * s);
		tmp.mtx[0][3] = 0.0f;

		tmp.mtx[1][0] = (y * x) * (1.0f - c) - (z * s);
		tmp.mtx[1][1] = (y * y) * (1.0f - c) + c;
		tmp.mtx[1][2] = (y * z) * (1.0f - c) + (x * s);
		tmp.mtx[1][3] = 0.0f;

		tmp.mtx[2][0] = (z * x) * (1.0f - c) + (y * s);
		tmp.mtx[2][1] = (z * y) * (1.0f - c) - (x * s);
		tmp.mtx[2][2] = (z * z) * (1.0f - c) + c;
		tmp.mtx[2][3] = 0.0f;

		tmp.mtx[3][0] = 0.0f;
		tmp.mtx[3][1] = 0.0f;
		tmp.mtx[3][2] = 0.0f;
		tmp.mtx[3][3] = 1.0f;

		return tmp;
	}

	Matrix4	Matrix4::RotateDeg(const Vector3& axis, float angle)
	{
		return RotateRad(axis, Math::Deg2Rad * angle);
	}

	Matrix4	Matrix4::Scale(const Vector3& scale)
	{
		Matrix4 tmp;
		tmp.mtx[0][0] = scale.x, tmp.mtx[0][1] = 0.0f, tmp.mtx[0][2] = 0.0f, tmp.mtx[0][3] = 0.0f;
		tmp.mtx[1][0] = 0.0f, tmp.mtx[1][1] = scale.y, tmp.mtx[1][2] = 0.0f, tmp.mtx[1][3] = 0.0f;
		tmp.mtx[2][0] = 0.0f, tmp.mtx[2][1] = 0.0f, tmp.mtx[2][2] = scale.z, tmp.mtx[2][3] = 0.0f;
		tmp.mtx[3][0] = 0.0f, tmp.mtx[3][1] = 0.0f, tmp.mtx[3][2] = 0.0f, tmp.mtx[3][3] = 1.0f;
		return tmp;
	}

	Matrix4	Matrix4::Scale(float scale)
	{
		return Scale(Vector3(scale));
	}

	Matrix4	Matrix4::Scale(float scalex, float scaley, float scalez)
	{
		return Scale(Vector3(scalex, scaley, scalez));
	}

	Matrix4 Matrix4::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale)
	{
		return rotation.ToMat4() * Translate(position) * Scale(scale);
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
