#pragma once
#include <Core/ValueType.h>

namespace uut
{
	class Radian;

	class Degree : public ValueType
	{
		UUT_STRUCT(Degree, ValueType)
	public:
		explicit constexpr Degree(float angle = 0.0f) : _angle(angle) {};
		Degree(const Radian& angle);

		float GetDegrees() const { return _angle; }
		float GetRadians() const;

		Degree& Clamp();
		Degree Clamped() const;

		Degree& operator= (const float& f) { _angle = f; return *this; }
		Degree& operator= (const Degree& d) { _angle = d._angle; return *this; }
		Degree& operator= (const Radian& r);

		const Degree& operator+ () const { return *this; }
		Degree operator- () const { return Degree(-_angle); }

		Degree operator+ (const Degree& d) const { return Degree(_angle + d._angle); }
		Degree operator+ (const Radian& r) const;

		Degree& operator+= (const Degree& d) { _angle += d._angle; return *this; }
		Degree& operator+= (const Radian& r);

		Degree operator- (const Degree& d) const { return Degree(_angle - d._angle); }
		Degree operator- (const Radian& r) const;

		Degree& operator-= (const Degree& d) { _angle -= d._angle; return *this; }
		Degree& operator-= (const Radian& r);

		Degree operator* (float f) const { return Degree(_angle * f); }
		Degree operator* (int i) const { return Degree(_angle * static_cast<float>(i)); }
		Degree operator* (const Degree& f) const { return Degree(_angle * f._angle); }

		Degree& operator*= (float f) { _angle *= f; return *this; }
		Degree operator/ (float f) const { return Degree(_angle / f); }
		Degree& operator/= (float f) { _angle /= f; return *this; }

		friend Degree operator* (float lhs, const Degree& rhs) { return Degree(lhs * rhs._angle); }
		friend Degree operator/ (float lhs, const Degree& rhs) { return Degree(lhs / rhs._angle); }
		friend Degree operator+ (Degree& lhs, float rhs) { return Degree(lhs._angle + rhs); }
		friend Degree operator+ (float lhs, const Degree& rhs) { return Degree(lhs + rhs._angle); }
		friend Degree operator- (const Degree& lhs, float rhs) { return Degree(lhs._angle - rhs); }
		friend Degree operator- (const float lhs, const Degree& rhs) { return Degree(lhs - rhs._angle); }

		bool operator<  (const Degree& d) const { return _angle < d._angle; }
		bool operator<= (const Degree& d) const { return _angle <= d._angle; }
		bool operator== (const Degree& d) const { return _angle == d._angle; }
		bool operator!= (const Degree& d) const { return _angle != d._angle; }
		bool operator>= (const Degree& d) const { return _angle >= d._angle; }
		bool operator>  (const Degree& d) const { return _angle > d._angle; }

		static const Degree Zero;

	protected:
		float _angle;
	};

	extern Degree operator"" _deg(long double angle);
	extern Degree operator"" _deg(unsigned long long int angle);

	UUT_DEFAULT(Degree, Degree::Zero)
}