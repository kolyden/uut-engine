#include "Plane.h"
#include "Vector3.h"
#include "Ray3.h"
#include "Math.h"

namespace uut
{
	const Plane Plane::Zero(0, 0, 0, 0);

	Plane::Plane()
	{
	}

	Plane::Plane(float fa, float fb, float fc, float fd)
		: a(fa), b(fb), c(fc), d(fd)
	{
	}

	Plane::Plane(const Vector3& point, const Vector3& normal)
		: a(normal.x)
		, b(normal.y)
		, c(normal.z)
		, d(Vector3::Dot(point, normal))
	{
	}

	Plane::Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	{
		Vector3 edge1 = Vector3::Sub(v2, v1);
		Vector3 edge2 = Vector3::Sub(v3, v1);
		Vector3 normal = Vector3::Cross(edge1, edge2).Normalized();

		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = Vector3::Dot(v1, normal);
	}

	Plane Plane::operator+() const
	{
		return *this;
	}

	Plane Plane::operator-() const
	{
		return Plane(-a, -b, -c, -d);
	}

	bool Plane::operator==(const Plane& pl) const
	{
		return a == pl.a && b == pl.b && c == pl.c && d == pl.d;
	}

	bool Plane::operator!=(const Plane& pl) const
	{
		return a != pl.a || b != pl.b || c != pl.c || d != pl.d;
	}

	Plane& Plane::Normalize()
	{
		const float norm = Math::Sqrt(a * a + b * b + c * c);
		if (norm)
		{
			a /= norm;
			b /= norm;
			c /= norm;
			d /= norm;
		}
		else
		{
			a = 0;
			b = 0;
			c = 0;
			d = 0;
		}

		return *this;
	}

	Plane Plane::Normalized() const
	{
		const float norm = Math::Sqrt(a * a + b * b + c * c);
		if (norm)
			return Plane(a / norm, b / norm, c / norm, d / norm);

		return Zero;
	}

	bool Plane::IntersectLine(const Vector3& v1, const Vector3& v2, Vector3& out) const
	{
		const Vector3 normal(a, b, c);
		const Vector3 direction = v2 - v1;
		const float dot = Vector3::Dot(normal, direction);
		if (!dot)
			return false;

		const float temp = d + Vector3::Dot(normal, v1) / dot;
		out = v1 - temp * direction;
		return true;
	}

	bool Plane::Intersect(const Ray3& ray, float& dist) const
	{
		const Vector3 normal(a, b, c);
		const float dot = Vector3::Dot(normal, ray.direction);
		if (!dot)
			return false;

		dist = d + Vector3::Dot(normal, ray.origin) / dot;
		return true;
	}
}