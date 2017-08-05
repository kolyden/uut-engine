#pragma once
#include "Fundamental.h"

namespace uut
{
	class Single : public ValueType, public FundamentalValue<float>
	{
		UUT_VALUETYPE(uut, Single, ValueType)
	public:
		constexpr Single() : FundamentalValue(0.0f) {}
		constexpr Single(float value) : FundamentalValue(value) {}

		String ToString() const;

		static const Single Zero;
		static const Single One;
		static const Single MaxValue;
		static const Single MinValue;

		static constexpr float DefaultValue = 0.0f;
	};

	UUT_FUNDAMENTAL(float, Single)
	UUT_DEFAULT_VALUE(Single, Single::Zero)
}