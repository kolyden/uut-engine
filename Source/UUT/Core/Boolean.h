#pragma once
#include <Core/Fundamental.h>
#include <Core/HashString.h>

namespace uut
{
	class Boolean : public ValueType, public FundamentalValue<bool>
	{
		UUT_STRUCT(Boolean, ValueType)
	public:
		constexpr Boolean() : FundamentalValue(false) {}
		constexpr Boolean(bool value) : FundamentalValue(value) {}

		Boolean& operator = (bool value)
		{
			_value = value;
			return *this;
		}

		static const Boolean Default;
		static const Boolean True;
		static const Boolean False;

		static const HashString TrueHash;
		static const HashString FalseHash;

		static constexpr bool DefaultValue = false;
	};

	UUT_FUNDAMENTAL(bool, Boolean)
}