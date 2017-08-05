#pragma once
#include "ValueType.h"
#include "Fundamental.h"

namespace uut
{
	class IntPtr : public ValueType, public FundamentalValue<void*>
	{
		UUT_VALUETYPE(uut, IntPtr, ValueType)
	public:
		constexpr IntPtr() : FundamentalValue(nullptr) {}
		explicit constexpr IntPtr(intptr_t value) : FundamentalValue(reinterpret_cast<void*>(value)) {}
		explicit constexpr IntPtr(void* ptr) : FundamentalValue(ptr) {}

		static constexpr void* DefaultValue = nullptr;

		static const IntPtr Empty;
	};

	namespace detail { template<>struct Fundamental<void*> { typedef IntPtr TYPE; }; }
	UUT_TYPEOF_VALUE(void*, IntPtr)
	template<> static constexpr void* const& GetDefault<void*>() \
	{ return IntPtr::DefaultValue; }
}