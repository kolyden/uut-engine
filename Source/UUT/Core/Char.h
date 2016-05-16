#pragma once
#include "ValueType.h"
#include "Fundamental.h"

namespace uut
{
	class Char : public ValueType, public FundamentalValue<uint16_t>
	{
		UUT_STRUCT(Char, ValueType)
	public:
		constexpr Char() : FundamentalValue(0) {}
		constexpr Char(char value) : FundamentalValue(value) {}
		constexpr Char(wchar_t value) : FundamentalValue(value) {}

		static constexpr uint16_t DefaultValue = 0;
	};

// 	UUT_FUNDAMENTAL(char, Char)
	UUT_FUNDAMENTAL(wchar_t, Char)
}