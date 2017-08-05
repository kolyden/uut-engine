#pragma once
#include "Templates/RangeBase.h"

namespace uut
{
	class Rangei : public RangeBase<int>
	{
		UUT_VALUETYPE(uut, Rangei, ValueType)
	public:
		constexpr Rangei() : RangeBase<int>(0, 0) {}
		constexpr Rangei(int imin, int imax) : RangeBase<int>(imin, imax) {}
		explicit constexpr Rangei(int val) : RangeBase<int>(val, val) {}

		int GetRandomValue() const;

		static const Rangei Zero;
	};

	UUT_TEST_VALUETYPE(Rangei);
	UUT_TEST_VALUETYPE_SIZE(Rangei, sizeof(int) * 2);
	UUT_DEFAULT_VALUE(Rangei, Rangei::Zero)
}