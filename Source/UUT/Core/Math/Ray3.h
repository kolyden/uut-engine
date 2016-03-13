#pragma once
#include "Vector3.h"

namespace uut
{
	class Ray3
	{
	public:
		Ray3();
		Ray3(const Vector3& pos, const Vector3& dir);

		Vector3 GetPoint(float dist) const;

		Vector3 origin;
		Vector3 direction;

		static const Ray3 Zero;
	};
}