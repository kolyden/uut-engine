#include "Ray3.h"

namespace uut
{
	Vector3 Ray3::GetPoint(float dist) const
	{
		return origin + direction * dist;
	}
}