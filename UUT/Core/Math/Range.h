#pragma once
#include "Templates/RangeBase.h"

namespace uut
{
	class Range : public RangeBase<float>
	{
		UUT_VALUETYPE(uut, Range, ValueType)
	public:
		constexpr Range() : RangeBase<float>(0, 0) {}
		constexpr Range(float fmin, float fmax) : RangeBase<float>(fmin, fmax) {}
		explicit constexpr Range(float val) : RangeBase<float>(val, val) {}

		float GetRandomValue() const;

		static const Range Zero;
	};

	static_assert(sizeof(Range) == sizeof(float) * 2, "Invalid Range size");
	UUT_DEFAULT_VALUE(Range, Range::Zero)
}