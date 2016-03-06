#pragma once

namespace uut
{
	class Degree;

	class Radian
	{
	public:
		explicit Radian(float angle = 0.0f) : _angle(angle) {}
		Radian(const Degree& angle);

		float GetDegrees() const;
		float GetRadians() const { return _angle; }

		Radian& Clamp();
		Radian Clamped() const;

		Radian& operator= (const float& f) { _angle = f; return *this; }
		Radian& operator= (const Radian& r) { _angle = r._angle; return *this; }
		Radian& operator= (const Degree& d);

		const Radian& operator+ () const { return *this; }
		Radian operator+ (const Radian& r) const { return Radian(_angle + r._angle); }
		Radian operator+ (const Degree& d) const;
		Radian& operator+= (const Radian& r) { _angle += r._angle; return *this; }
		Radian& operator+= (const Degree& d);
		Radian operator- () const { return Radian(-_angle); }
		Radian operator- (const Radian& r) const { return Radian(_angle - r._angle); }
		Radian operator- (const Degree& d) const;
		Radian& operator-= (const Radian& r) { _angle -= r._angle; return *this; }
		Radian& operator-= (const Degree& d);
		Radian operator* (float f) const { return Radian(_angle * f); }
		Radian operator* (const Radian& f) const { return Radian(_angle * f._angle); }
		Radian& operator*= (float f) { _angle *= f; return *this; }
		Radian operator/ (float f) const { return Radian(_angle / f); }
		Radian& operator/= (float f) { _angle /= f; return *this; }

		friend Radian operator* (float lhs, const Radian& rhs) { return Radian(lhs * rhs._angle); }
		friend Radian operator/ (float lhs, const Radian& rhs) { return Radian(lhs / rhs._angle); }
		friend Radian operator+ (Radian& lhs, float rhs) { return Radian(lhs._angle + rhs); }
		friend Radian operator+ (float lhs, const Radian& rhs) { return Radian(lhs + rhs._angle); }
		friend Radian operator- (const Radian& lhs, float rhs) { return Radian(lhs._angle - rhs); }
		friend Radian operator- (const float lhs, const Radian& rhs) { return Radian(lhs - rhs._angle); }

		bool operator<  (const Radian& r) const { return _angle < r._angle; }
		bool operator<= (const Radian& r) const { return _angle <= r._angle; }
		bool operator== (const Radian& r) const { return _angle == r._angle; }
		bool operator!= (const Radian& r) const { return _angle != r._angle; }
		bool operator>= (const Radian& r) const { return _angle >= r._angle; }
		bool operator>  (const Radian& r) const { return _angle > r._angle; }

		static const Radian EMPTY;

	protected:
		float _angle;
	};
}