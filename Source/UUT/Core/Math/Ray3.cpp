#include "Ray3.h"

namespace uut
{
	const Ray3 Ray3::Zero(Vector3::Zero, Vector3::Zero);

	Ray3::Ray3()
		: origin(Vector3::Zero)
		, direction(Vector3::Forward)
	{
	}

	Ray3::Ray3(const Vector3& pos, const Vector3& dir)
		: origin(pos)
		, direction(dir)
	{
	}

	Vector3 Ray3::GetPoint(float dist) const
	{
		return origin + direction * dist;
	}
}