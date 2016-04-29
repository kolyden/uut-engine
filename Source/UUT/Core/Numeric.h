#pragma once
#include <Core/ValueType.h>
#include <limits>

namespace uut
{
	template<typename T>
	class Numeric : public ValueType
	{
		UUT_STRUCT(Numeric, ValueType)
	public:
		Numeric() : _value(0) {}
		explicit Numeric(T value) : _value(value) {}

		operator T() const { return _value; }

		Numeric<T>& operator = (T value)
		{
			_value = value;
			return *this;
		}

		bool operator == (T other) const { return _value == other; }
		bool operator != (T other) const { return _value != other; }
		bool operator <= (T other) const { return _value <= other; }
		bool operator >= (T other) const { return _value >= other; }
		bool operator < (T other) const { return _value < other; }
		bool operator > (T other) const { return _value > other; }

		static const T MaxValue;
		static const T MinValue;
		static const Numeric<T> Zero;
		static const Numeric<T> One;

	protected:
		T _value;
	};

	template<typename T>const T Numeric<T>::MaxValue = std::numeric_limits<T>::max();
	template<typename T>const T Numeric<T>::MinValue = std::numeric_limits<T>::min();
	template<typename T>const Numeric<T> Numeric<T>::Zero(0);
	template<typename T>const Numeric<T> Numeric<T>::One(1);

	/*
	namespace internal { template<>const char* NumericFormat<int>::NAME = "int"; }
	template<>
	static const Type* typeof<int>()
	{
		return typeof<Numeric<int>>();
	}
	//*/

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

#define UUT_NUMERIC(type) \
	template<> static const Type* typeof<type>() \
	{ return typeof<Numeric<type>>(); }

#define UUT_NUMERIC_IMPLEMENT(type) UUT_STRUCT_IMPLEMENT(Numeric<type>)

	UUT_NUMERIC(bool);
	UUT_NUMERIC(int8_t);
	UUT_NUMERIC(uint8_t);
	UUT_NUMERIC(int16_t);
	UUT_NUMERIC(uint16_t);
	UUT_NUMERIC(int32_t);
	UUT_NUMERIC(uint32_t);
	UUT_NUMERIC(int64_t);
	UUT_NUMERIC(uint64_t);
	UUT_NUMERIC(float);
	UUT_NUMERIC(double);

#define UUT_REGISTER_NUMERIC(type) UUT_REGISTER_TYPE(TypeInfo::Struct, Numeric<type>, #type)
}