#pragma once
#include <Core/Fundamental.h>
#include <limits>

namespace uut
{
	template<typename T>
	class Numeric : public ValueType, public FundamentalValue<T>
	{
// 		UUT_STRUCT(Numeric, Fundamental)
	public:
		Numeric() : FundamentalValue(0) {}
		explicit constexpr Numeric(T value) : FundamentalValue(value) {}

// 		Numeric<T>& operator = (T value)
// 		{
// 			FundamentalValue<T>::_value = value;
// 			return *this;
// 		}

		static const T MaxValue;
		static const T MinValue;
		static const Numeric<T> Zero;
		static const Numeric<T> One;
		static const Numeric<T> Default;

		static constexpr T DefaultValue = static_cast<T>(0);
	};

	template<typename T>const T Numeric<T>::MaxValue = std::numeric_limits<T>::max();
	template<typename T>const T Numeric<T>::MinValue = std::numeric_limits<T>::min();
	template<typename T>const Numeric<T> Numeric<T>::Zero(0);
	template<typename T>const Numeric<T> Numeric<T>::One(1);
	template<typename T>const Numeric<T> Numeric<T>::Default(0);



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
	class name : public Numeric<type> \
	{ UUT_STRUCT(name, ValueType) }; \
 	UUT_FUNDAMENTAL(type, name)

// #define UUT_NUMERIC_IMPLEMENT(name, type) \
// 	UUT_STRUCT_IMPLEMENT(Numeric<type>) {} \
// 	UUT_STRUCT_IMPLEMENT(name)

	UUT_NUMERIC(Int8, int8_t);
	UUT_NUMERIC(UInt8, uint8_t);
	UUT_NUMERIC(Int16, int16_t);
	UUT_NUMERIC(UInt16, uint16_t);
	UUT_NUMERIC(Int32, int32_t);
	UUT_NUMERIC(UInt32, uint32_t);
	UUT_NUMERIC(Int64, int64_t);
	UUT_NUMERIC(UInt64, uint64_t);
}