#pragma once
#include <Core/Fundamental.h>
#include <limits>
#include "String.h"

namespace uut
{
	template<typename T>
	class Numeric : public FundamentalValue<T>
	{
	public:
		constexpr Numeric() : FundamentalValue(0) {}
		explicit constexpr Numeric(T value) : FundamentalValue(value) {}

// 		Numeric<T>& operator = (T value)
// 		{
// 			FundamentalValue<T>::_value = value;
// 			return *this;
// 		}

		String ToString() const { return std::to_string(FundamentalValue<T>::GetValue()); }

		static const T MaxValue;
		static const T MinValue;

		static constexpr T DefaultValue = static_cast<T>(0);
	};

	template<typename T>const T Numeric<T>::MaxValue = std::numeric_limits<T>::max();
	template<typename T>const T Numeric<T>::MinValue = std::numeric_limits<T>::min();

// #define UUT_NUMERIC(name, type) \
// 	class name : public Numeric<type> \
// 	{ UUT_STRUCT(name, Numeric<type>) } \
// 
// #define UUT_NUMERIC_IMPLEMENT(type) UUT_STRUCT_IMPLEMENT(type) {}
// 
// 	UUT_NUMERIC(Int8, int8_t);
// 	UUT_NUMERIC(UInt8, uint8_t);
// 	UUT_NUMERIC(Int16, int16_t);
// 	UUT_NUMERIC(UInt16, uint16_t);
// 	UUT_NUMERIC(Int32, int32_t);
// 	UUT_NUMERIC(UInt32, uint32_t);
// 	UUT_NUMERIC(Int64, int64_t);
// 	UUT_NUMERIC(UInt64, uint64_t);
// 	UUT_NUMERIC(Float, float);
// 	UUT_NUMERIC(Double, double);


#define UUT_NUMERIC(name, type) \
	class name : public ValueType, public Numeric<type> \
	{ UUT_STRUCT(name, ValueType) \
	public: constexpr name() {} \
	constexpr name(type value) : Numeric(value) {} \
	static const name Zero; }; \
 	UUT_FUNDAMENTAL(type, name) \
	UUT_DEFAULT(name, name::Zero)

#define UUT_NUMERIC_IMPLEMENT(name) \
	const name name::Zero(0); \
	UUT_STRUCT_IMPLEMENT(name)

	UUT_NUMERIC(Int8, int8_t)
	UUT_NUMERIC(UInt8, uint8_t)
	UUT_NUMERIC(Int16, int16_t)
	UUT_NUMERIC(UInt16, uint16_t)
	UUT_NUMERIC(Int32, int32_t)
	UUT_NUMERIC(UInt32, uint32_t)
	UUT_NUMERIC(Int64, int64_t)
	UUT_NUMERIC(UInt64, uint64_t)
}
