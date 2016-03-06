#pragma once
#include "Radian.h"
#include "Degree.h"

namespace uut
{
	class Math
	{
	public:
		static const float PI;
		static const float TWO_PI;
		static const float HALF_PI;

		static const float POS_INFINITY;
		static const float NEG_INFINITY;
		static const float RAD2DEG;
		static const float DEG2RAD;
		static const float Epsilon;

		static float Sin(float f);
		static float Sin(const Radian& f);

		static float Cos(float f);
		static float Cos(const Radian& f);

		static void SinCos(float angle, float& sin, float& cos);
		static void SinCos(const Radian& angle, float& sin, float& cos);

		static float Tan(float f);
		static float Tan(const Radian& f);

		static float Cot(float f);
		static float Cot(const Radian& f);

		static Radian Asin(float f);
		static Radian Acos(float f);
		static Radian Atan(float f);
		static Radian Atan2(float y, float x);

		static float Sqrt(float f);
		static Radian Sqrt(const Radian& f);
		static Degree Sqrt(const Degree& f);

		static float Abs(float f);
		static Radian Abs(const Radian& f);
		static Degree Abs(const Degree& f);

		static float Min(float a, float b);
		static int Min(int a, int b);
// 		static int Min(const List<int>& values);
// 		static float Min(const List<float>& values);

		static float Max(float a, float b);
		static int Max(int a, int b);
// 		static int Max(const List<int>& values);
// 		static float Max(const List<float>& values);

		static float Pow(float f, float p);
		static float Exp(float power);
		static float Log(float f);
		static float Log10(float f);

		static float Ceil(float f);
		static float Floor(float f);
		static float Round(float f);

		static int CeilToInt(float f);
		static int FloorToInt(float f);
		static int RoundToInt(float f);

		static float Sign(float f);

		static float Clamp(float val, float min, float max);
		static int Clamp(int val, int min, int max);
		static float Clamp01(float val);

		static float Lerp(float from, float to, float t);
// 		static float LerpAngle(float a, float b, float t);
// 		static float MoveTowards(float current, float target, float maxDelta);

		static bool Approximately(float a, float b);
		static bool IsNaN(float value);

		static float Repeat(float t, float length);
		static float PingPong(float t, float length);

		static float DeltaAngle(float current, float target);

// 		static bool LineIntersect(const vec2f& p1, const vec2f& p2, const vec2f& p3, const vec2f& p4, vec2f* result);
// 		static bool LineSegmentIntersect(const vec2f& p1, const vec2f& p2, const vec2f& p3, const vec2f& p4, vec2f* result);

	private:
		Math() = delete;
	};
}