#pragma once

namespace uut
{
	class Ray3;
	class Vector3;

	class Plane
	{
	public:
		Plane();
		Plane(float fa, float fb, float fc, float fd);
		Plane(const Vector3& point, const Vector3& normal);
		Plane(const Vector3& v1, const Vector3& v2, const Vector3& v3);

		operator float* () { return data; }
		operator const float* () const { return data; }

		Plane operator + () const;
		Plane operator - () const;

		bool operator == (const Plane& p) const;
		bool operator != (const Plane& p) const;

		Plane& Normalize();
		Plane Normalized() const;

		bool IntersectLine(const Vector3& v1, const Vector3& v2, Vector3& out) const;

		static const Plane Zero;

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