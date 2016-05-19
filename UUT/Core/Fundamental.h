#pragma once
#include "ValueType.h"

namespace uut
{
	template<class C>
	class FundamentalValue
	{
	public:
		explicit constexpr FundamentalValue(C value) : _value(value) {}

		operator C() const { return _value; }
		operator C&() { return _value; }

		C GetValue() const { return _value; }

		bool operator == (C other) const { return _value == other; }
		bool operator != (C other) const { return _value != other; }
		bool operator <= (C other) const { return _value <= other; }
		bool operator >= (C other) const { return _value >= other; }
		bool operator < (C other) const { return _value < other; }
		bool operator > (C other) const { return _value > other; }

	protected:
		C _value;
	};

	namespace detail
	{
		template<class C> struct Fundamental {};
	}

#define UUT_FUNDAMENTAL(type, value) \
	namespace detail { template<>struct Fundamental<type> { typedef value TYPE; }; } \
	UUT_VALUE_TYPE(type, value) \
	UUT_DEFAULT(type, value::DefaultValue)
}