#pragma once
#include <Core/Fundamental.h>
#include <limits>
#include "Number.h"
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

		String ToString() const { return Number::ToString(FundamentalValue<T>::GetValue()); }
		static T Parse(const String& value) { return Number::ToNumeric<T>(value); }

		static const T MaxValue;
		static const T MinValue;

		static constexpr T DefaultValue = static_cast<T>(0);
	};

	template<typename T>const T Numeric<T>::MaxValue = std::numeric_limits<T>::max();
	template<typename T>const T Numeric<T>::MinValue = std::numeric_limits<T>::min();

// #define UUT_NUMERIC(name, type) \
// 	class name : public Numeric<type> \
// 	{ UUT_VALUETYPE(name, Numeric<type>) } \
// 
// #define UUT_NUMERIC_IMPLEMENT(type) UUT_VALUETYPE_IMPLEMENT(type) {}
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

#define UUT_NUMERIC_OPERATORS(type) \
	Numeric<type> operator+ (type value) const { return Numeric<type>(_value + value); } \
	Numeric<type> operator- (type value) const { return Numeric<type>(_value - value); } \
	Numeric<type> operator* (type value) const { return Numeric<type>(_value * value); } \
	Numeric<type> operator/ (type value) const { return Numeric<type>(_value / value); } \
	Numeric<type> operator+ (const Numeric<type>& value) const { return Numeric<type>(_value + value); } \
	Numeric<type> operator- (const Numeric<type>& value) const { return Numeric<type>(_value - value); } \
	Numeric<type> operator* (const Numeric<type>& value) const { return Numeric<type>(_value * value); } \
	Numeric<type> operator/ (const Numeric<type>& value) const { return Numeric<type>(_value / value); } \
	Numeric<type>& operator+= (type value) { _value += value; return *this; } \
	Numeric<type>& operator-= (type value) { _value -= value; return *this; } \
	Numeric<type>& operator*= (type value) { _value *= value; return *this; } \
	Numeric<type>& operator/= (type value) { _value /= value; return *this; }


#define UUT_NUMERIC(library, name, type) \
	class name : public ValueType, public Numeric<type> \
	{ UUT_VALUETYPE(library, name, ValueType) \
	public: constexpr name() {} \
	constexpr name(type value) : Numeric(value) {} \
	UUT_NUMERIC_OPERATORS(type) \
	static const name Zero; }; \
 	UUT_FUNDAMENTAL(type, name) \
	UUT_DEFAULT_VALUE(name, name::Zero)

#define UUT_NUMERIC_IMPLEMENT(name) \
	const name name::Zero(0); \
	UUT_VALUETYPE_IMPLEMENT(name)

	UUT_NUMERIC(uut, Int8, int8_t)
	UUT_NUMERIC(uut, UInt8, uint8_t)
	UUT_NUMERIC(uut, Int16, int16_t)
	UUT_NUMERIC(uut, UInt16, uint16_t)
	UUT_NUMERIC(uut, Int32, int32_t)
	UUT_NUMERIC(uut, UInt32, uint32_t)
	UUT_NUMERIC(uut, Int64, int64_t)
	UUT_NUMERIC(uut, UInt64, uint64_t)
}