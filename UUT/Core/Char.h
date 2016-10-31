#pragma once
#include "ValueType.h"
#include "Fundamental.h"
#include "StringComparison.h"

namespace uut
{
	class Char
		: public ValueType
		, public FundamentalValue<uint16_t>
	{
		UUT_VALUETYPE(uut, Char, ValueType)
	public:
		constexpr Char() : FundamentalValue(0) {}
		constexpr Char(char value) : FundamentalValue(value) {}
		constexpr Char(wchar_t value) : FundamentalValue(value) {}

		static int Compare(char a, char b, StringComparison comparisonType = StringComparison::Ordinal);

		static constexpr uint16_t DefaultValue = 0;

		static const List<char> WhiteSpaces;
		static bool IsWhiteSpace(char c);
	};

// 	UUT_FUNDAMENTAL(char, Char)
	UUT_FUNDAMENTAL(wchar_t, Char)
}