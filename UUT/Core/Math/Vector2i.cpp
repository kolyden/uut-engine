#include "Vector2i.h"
#include <algorithm>
#include "Math.h"
#include "Vector2.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Vector2i)
	{
		UUT_REGISTER_CTOR(Vector2);
		UUT_REGISTER_CONVERTER_DEFAULT(Vector2);
	}

	const Vector2i Vector2i::Default(0, 0);
	const Vector2i Vector2i::Zero(0, 0);
	const Vector2i Vector2i::One(1, 1);
	const Vector2i Vector2i::Left(-1, 0);
	const Vector2i Vector2i::Right(1, 0);
	const Vector2i Vector2i::Up(0, 1);
	const Vector2i Vector2i::Down(0, -1);

	Vector2i::Vector2i(const Vector2& vec)
		: Vector2Data<int>(
			Math::RoundToInt(vec.x),
			Math::RoundToInt(vec.y))
	{
	}

	float Vector2i::Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	Vector2i& Vector2i::operator+=(const Vector2i& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2i& Vector2i::operator-=(const Vector2i& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2i& Vector2i::operator*=(int s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vector2i Vector2i::operator+() const
	{
		return *this;
	}

	Vector2i Vector2i::operator-() const
	{
		return Vector2i(-x, -y);
	}

	Vector2i Vector2i::operator+(const Vector2i& vec) const
	{
		return Vector2i(x + vec.x, y + vec.y);
	}

	Vector2i Vector2i::operator-(const Vector2i& vec) const
	{
		return Vector2i(x - vec.x, y - vec.y);
	}

	Vector2i Vector2i::operator*(int s) const
	{
		return Vector2i(x * s, y * s);
	}

	Vector2i& Vector2i::operator=(const Vector2i& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2i& Vector2i::operator=(Vector2i&& vec)
	{
		std::swap(x, vec.x);
		std::swap(y, vec.y);
		return *this;
	}

	Vector2i Vector2i::Lerp(const Vector2i& a, const Vector2i& b, float s)
	{
		return Vector2i(
			Math::RoundToInt((1 - s) * (a.x) + s * (b.x)),
			Math::RoundToInt((1 - s) * (a.y) + s * (b.y)));
	}

	float Vector2i::Distance(const Vector2i& a, const Vector2i& b)
	{
		return Math::Sqrt(DistanceSq(a, b));
	}
}