#pragma once
#include "Templates/RangeBase.h"

namespace uut
{
	class IntRange : public RangeBase<int>
	{
		UUT_VALUETYPE(uut, IntRange, ValueType)
	public:
		constexpr IntRange() : RangeBase<int>(0, 0) {}
		constexpr IntRange(int imin, int imax) : RangeBase<int>(imin, imax) {}
		explicit constexpr IntRange(int val) : RangeBase<int>(val, val) {}

		int GetRandomValue() const;

		static const IntRange Zero;
	};

	static_assert(sizeof(IntRange) == sizeof(int) * 2, "Invalid IntRange size");
	UUT_DEFAULT(IntRange, IntRange::Zero)
}