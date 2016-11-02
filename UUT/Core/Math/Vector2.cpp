#include "Vector2.h"
#include "IntVector2.h"
#include "Math.h"
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Vector2)
	{
		UUT_REGISTER_CTOR(IntVector2);
		UUT_REGISTER_CONVERTER_DEFAULT(IntVector2);

		UUT_REGISTER_PROPERTY("x", float, x);
		UUT_REGISTER_PROPERTY("y", float, y);

		internalType->AddMember(
			new PropertyInfo<Vector2, float>("length",
				[](const Vector2* obj) -> float { return obj->Length(); }, nullptr));
	}

	const Vector2 Vector2::Zero(0);
	const Vector2 Vector2::One(1);
	const Vector2 Vector2::Left(-1, 0);
	const Vector2 Vector2::Right(1, 0);
	const Vector2 Vector2::Up(0, 1);
	const Vector2 Vector2::Down(0, -1);

	Vector2::Vector2(const IntVector2& vec)
		: Vector2Data<float>(
			static_cast<float>(vec.x),
			static_cast<float>(vec.y))
	{
	}

	float Vector2::Length() const
	{
		return Math::Sqrt(LengthSq());
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

		return Zero;
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

	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		return Math::Sqrt(DistanceSq(a, b));
	}
}