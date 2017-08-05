#pragma once
#include "Fundamental.h"
#include "Single.h"

namespace uut
{
	class Double : public ValueType, public FundamentalValue<double>
	{
		UUT_VALUETYPE(uut, Double, ValueType)
	public:
		constexpr Double() : FundamentalValue(0.0) {}
		constexpr Double(double value) : FundamentalValue(value) {}

		static const Double Zero;
		static const Double One;
		static const Double MaxValue;
		static const Double MinValue;

		static constexpr double DefaultValue = 0.0;
	};

	UUT_FUNDAMENTAL(double, Single)
	UUT_DEFAULT_VALUE(Double, Double::Zero)
}