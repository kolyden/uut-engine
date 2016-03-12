#pragma once
#include "Vector3.h"

namespace uut
{
	class Ray3
	{
	public:
		Vector3 origin;
		Vector3 direction;

		Vector3 GetPoint(float dist) const;
	};
}