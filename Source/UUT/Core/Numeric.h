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
		static const T MaxValue;
		static const T MinValue;
	};

	template<typename T>const T Numeric<T>::MaxValue = std::numeric_limits<T>::max();
	template<typename T>const T Numeric<T>::MinValue = std::numeric_limits<T>::min();

	/*
	namespace internal { template<>const char* NumericFormat<int>::NAME = "int"; }
	template<>
	static const Type* typeof<int>()
	{
		return typeof<Numeric<int>>();
	}
	//*/

#define UUT_NUMERIC(type) UUT_STRUCT_IMPLEMENT(Numeric<type>) {}

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

#define UUT_REGISTER_NUMERIC(type) \
	Context::RegisterType<Numeric<type>>(TypeInfo::Struct, #type, &Numeric<type>::_RegisterInternal);
}