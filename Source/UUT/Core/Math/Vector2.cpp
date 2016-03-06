#include "Vector2.h"
#include "IntVector2.h"
#include "Math.h"

namespace uut
{
	const Vector2 Vector2::ZERO(0);
	const Vector2 Vector2::ONE(1);
	const Vector2 Vector2::AXIS_X(1, 0);
	const Vector2 Vector2::AXIS_Y(0, 1);

	Vector2::Vector2()
	{
	}

	Vector2::Vector2(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Vector2::Vector2(float val)
		: x(val), y(val)
	{
	}

	Vector2::Vector2(const IntVector2& vec)
		: x(static_cast<float>(vec.x))
		, y(static_cast<float>(vec.y))
	{
	}

	Vector2& Vector2::operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2& Vector2::operator/=(float s)
	{
		x /= s;
		y /= s;
		return *this;
	}

	Vector2 Vector2::operator+() const
	{
		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	Vector2 Vector2::operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	Vector2 Vector2::operator*(float s) const
	{
		return Vector2(x * s, y * s);
	}

	Vector2 Vector2::operator/(float s) const
	{
		return Vector2(x / s, y / s);
	}

	bool Vector2::operator==(const Vector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	bool Vector2::operator!=(const Vector2& vec) const
	{
		return x != vec.x || y != vec.y;
	}

	float Vector2::Length() const
	{
		return Math::Sqrt(x*x + y*y);
	}

	float Vector2::LengthSq() const
	{
		return x*x + y*y;
	}

	Vector2& Vector2::Normalize()
	{
		const float norm = Length();
		if (norm)
		{
			x /= norm;
			y /= norm;
		}
		else
		{
			x = 0;
			y = 0;
		}

		return *this;
	}

	Vector2 Vector2::Normalized() const
	{
		const float norm = Length();
		if (norm)
		{
			return Vector2(
				x / norm,
				y / norm);
		}

		return ZERO;
	}

	Vector2 Vector2::Add(const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x + v2.x, v1.y + v2.y);
	}

	Vector2 Vector2::Sub(const Vector2& v1, const Vector2& v2)
	{
		return Vector2(v1.x - v2.x, v1.y - v2.y);
	}

	float Vector2::CCW(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	float Vector2::Dot(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float s)
	{
		return Vector2(
			(1 - s) * (a.x) + s * (b.x),
			(1 - s) * (a.y) + s * (b.y));
	}

	Vector2 Vector2::Maximize(const Vector2& a, const Vector2& b)
	{
		return Vector2(
			a.x > b.x ? a.x : b.x,
			a.y > b.y ? a.y : b.y);
	}

	Vector2 Vector2::Minimize(const Vector2& a, const Vector2& b)
	{
		return Vector2(
			a.x < b.x ? a.x : b.x,
			a.y < b.y ? a.y : b.y);
	}

	Vector2 Vector2::Scale(const Vector2& vec, float s)
	{
		return Vector2(s*vec.x, s*vec.y);
	}
}