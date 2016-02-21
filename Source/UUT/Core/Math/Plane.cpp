#include "Plane.h"
#include "Vector3.h"
#include "Ray3.h"

namespace uut
{
	Plane::Plane()
	{
	}

	Plane::Plane(float _a, float _b, float _c, float _d)
		: a(_a), b(_b), c(_c), d(_d)
	{
	}

	Plane::Plane(const Vector3& normal, float dist)
		: a(normal.x), b(normal.y), c(normal.z), d(-dist)
	{
	}

	Plane::Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3)
	{
		auto normal = (p1 - p2).Cross(p3 - p2);
		normal.Normalize();
		
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -normal.Dot(p2);
	}

	bool Plane::Intersect(const Ray3& ray, float& dist) const
	{
		float d1, d2;

		Vector3 normal(a, b, c);
		d1 = normal.Dot(ray.origin) + d;
		d2 = normal.Dot(ray.direction);
		if (d2 == 0.0f)
			return false;

		dist = -(d1 / d2);
		return true;
	}
}