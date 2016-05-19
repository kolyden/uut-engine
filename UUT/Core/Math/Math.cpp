#include "Math.h"
#include <limits>

namespace uut
{
	const Radian Math::PI(3.141592654f);
	const Radian Math::TWO_PI = PI * 2.0f;
	const Radian Math::HALF_PI = PI / 2.0f;

	const float Math::POS_INFINITY = std::numeric_limits<float>::max();
	const float Math::NEG_INFINITY = -std::numeric_limits<float>::min();
	const float Math::RAD2DEG = (180.0f / PI).GetRadians();
	const float Math::DEG2RAD = (PI / 180.0f).GetRadians();
	const float Math::Epsilon = 0.000001f;

	float Math::Sin(float f) { return ::sin(f); }

	float Math::Sin(const Radian& f)
	{
		return std::sin(f.GetRadians());
	}

	float Math::Cos(float f) { return ::cos(f); }

	float Math::Cos(const Radian& f)
	{
		return std::cos(f.GetRadians());
	}

	void Math::SinCos(float angle, float& sin, float& cos)
	{
		sin = Sin(angle);
		cos = Cos(angle);
	}

	void Math::SinCos(const Radian& angle, float& sin, float& cos)
	{
		sin = Sin(angle.GetRadians());
		cos = Cos(angle.GetRadians());
	}

	float Math::Tan(float f) { return ::tan(f); }

	float Math::Tan(const Radian& f)
	{
		return std::tan(f.GetRadians());
	}

	float Math::Cot(float f) { return 1.0f / ::tan(f); }

	float Math::Cot(const Radian& f)
	{
		return Cot(f.GetRadians());
	}

	Radian Math::Asin(float f) { return Radian(::asin(f)); }

	Radian Math::Acos(float f) { return Radian(::acos(f)); }

	Radian Math::Atan(float f) { return Radian(::atan(f)); }

	Radian Math::Atan2(float y, float x) { return Radian(::atan2(y, x)); }

	float Math::Sqrt(float f) { return ::sqrt(f); }

	Radian Math::Sqrt(const Radian& f)
	{
		return Radian(std::sqrtf(f.GetRadians()));
	}

	Degree Math::Sqrt(const Degree& f)
	{
		return Degree(std::sqrtf(f.GetDegrees()));
	}

	float Math::Abs(float f) { return ::abs(f); }

	Radian Math::Abs(const Radian& f)
	{
		return Radian(std::abs(f.GetRadians()));
	}

	Degree Math::Abs(const Degree& f)
	{
		return Degree(std::abs(f.GetDegrees()));
	}

	float Math::Min(float a, float b) { return a >= b ? b : a; }

	int Math::Min(int a, int b) { return a >= b ? b : a; }

// 	int Mathf::Min(const List<int>& values)
// 	{
// 		if (values.IsEmpty())
// 			return 0;
// 
// 		int val = values[0];
// 		for (int i = 1; i < values.Count(); i++)
// 		{
// 			if (val < values[i])
// 				val = values[i];
// 		}
// 
// 		return val;
// 	}
// 
// 	float Mathf::Min(const List<float>& values)
// 	{
// 		if (values.IsEmpty())
// 			return 0.0f;
// 
// 		float val = values[0];
// 		for (int i = 1; i < values.Count(); i++)
// 		{
// 			if (val < values[i])
// 				val = values[i];
// 		}
// 
// 		return val;
// 	}

	float Math::Max(float a, float b) { return a <= b ? b : a; }

	int Math::Max(int a, int b) { return a <= b ? b : a; }

// 	int Mathf::Max(const List<int>& values)
// 	{
// 		if (values.IsEmpty())
// 			return 0;
// 
// 		int val = values[0];
// 		for (int i = 1; i < values.Count(); i++)
// 		{
// 			if (val > values[i])
// 				val = values[i];
// 		}
// 
// 		return val;
// 	}

// 	float Mathf::Max(const List<float>& values)
// 	{
// 		if (values.IsEmpty())
// 			return 0.0f;
// 
// 		float val = values[0];
// 		for (int i = 1; i < values.Count(); i++)
// 		{
// 			if (val > values[i])
// 				val = values[i];
// 		}
// 
// 		return val;
// 	}

	float Math::Pow(float f, float p) { return ::pow(f, p); }

	float Math::Exp(float power) { return ::exp(power); }

	float Math::Log(float f) { return ::log(f); }

	float Math::Log10(float f) { return ::log10(f); }

	float Math::Ceil(float f) { return ::ceil(f); }

	float Math::Floor(float f) { return ::floor(f); }

	float Math::Round(float f) { return ::round(f); }

	int Math::CeilToInt(float f) { return static_cast<int>(Ceil(f)); }

	int Math::FloorToInt(float f) { return static_cast<int>(Floor(f)); }

	int Math::RoundToInt(float f) { return static_cast<int>(Round(f)); }

	float Math::Sign(float f) { return f < 0 ? -1.0f : 1.0f; }

	float Math::Clamp(float val, float min, float max)
	{
		if (val < min)
			return min;
		if (val > max)
			return max;
		return val;
	}

	int Math::Clamp(int val, int min, int max)
	{
		if (val < min)
			return min;
		if (val > max)
			return max;
		return val;
	}

	float Math::Clamp01(float val)
	{
		if (val < 0.0f)
			return 0.0f;
		if (val > 1.0f)
			return 1.0f;
		return val;
	}

	float Math::Lerp(float from, float to, float t)
	{
		return from + (to - from)*Clamp01(t);
	}

// 	float Mathf::LerpAngle(float a, float b, float t)
// 	{
// 		const float delta = Math::angledelta(a, b);
// 		return a + delta * Clamp01(t);
// 	}

// 	float Mathf::MoveTowards(float current, float target, float maxDelta)
// 	{
// 	}

	bool Math::Approximately(float a, float b)
	{
		return Abs(b - a) < Max(1e-06f * Max(Abs(a), Abs(b)), Epsilon * 8.0f);
	}

#ifndef __GNUC__
	bool Math::IsNaN(float value) { return value != value; }
#else

	bool Math::IsNaN(float value)
	{
		unsigned u = *(unsigned*)(&value);
		return (u & 0x7fffffff) > 0x7f800000;
	}

#endif

	float Math::Repeat(float t, float length) { return t - Floor(t / length) *length; }

	float Math::PingPong(float t, float length)
	{
		t = Repeat(t, length * 2.0f);
		return length - Abs(t - length);
	}

	float Math::DeltaAngle(float current, float target)
	{
		float num = Repeat(target - current, 360.0f);
		if (num > 180.0f)
			num -= 360.0f;
		return num;
	}

// 	bool Mathf::LineIntersect(const vec2f& p1, const vec2f& p2, const vec2f& p3, const vec2f& p4, vec2f* result)
// 	{
// 		const float num = p2.x - p1.x;
// 		const float num2 = p2.y - p1.y;
// 		const float num3 = p4.x - p3.x;
// 		const float num4 = p4.y - p3.y;
// 		const float num5 = num * num4 - num2 * num3;
// 		if (num5 == 0.0f)
// 			return false;
// 
// 		if (result != nullptr)
// 		{
// 			const float num6 = p3.x - p1.x;
// 			const float num7 = p3.y - p1.y;
// 			const float num8 = (num6 * num4 - num7 * num3) / num5;
// 			*result = vec2f(p1.x + num8 * num, p1.y + num8 * num2);
// 		}
// 
// 		return true;
// 	}

// 	bool Mathf::LineSegmentIntersect(const vec2f& p1, const vec2f& p2, const vec2f& p3, const vec2f& p4, vec2f* result)
// 	{
// 		const float num = p2.x - p1.x;
// 		const float num2 = p2.y - p1.y;
// 		const float num3 = p4.x - p3.x;
// 		const float num4 = p4.y - p3.y;
// 		const float num5 = num * num4 - num2 * num3;
// 		if (num5 == 0.0f)
// 			return false;
// 
// 		const float num6 = p3.x - p1.x;
// 		const float num7 = p3.y - p1.y;
// 		const float num8 = (num6 * num4 - num7 * num3) / num5;
// 		if (num8 < 0.0f || num8 > 1.0f)
// 			return false;
// 
// 		const float num9 = (num6 * num2 - num7 * num) / num5;
// 		if (num9 < 0.0f || num9 > 1.0f)
// 			return false;
// 
// 		if (result != nullptr)
// 			*result = vec2f(p1.x + num8 * num, p1.y + num8 * num2);
// 
// 		return true;
// 	}
}
