#pragma once

namespace uut
{
	class Ray3;
	class Vector3;

	class Plane
	{
	public:
		Plane();
		Plane(float a, float b, float c, float d);
		Plane(const Vector3& normal, float dist);
		Plane(const Vector3& p1, const Vector3& p2, const Vector3& p3);

		bool Intersect(const Ray3& ray, float& dist) const;

		union
		{
			float data[4];
			struct
			{
				float a;
				float b;
				float c;
				float d;
			};
		};
	};
}