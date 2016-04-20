#pragma once
#include <Core/ValueType.h>
#include <limits>

namespace uut
{
	namespace internal
	{
		template<typename T>
		struct NumericFormat
		{
			static const char* NAME;
		};
	}

	template<typename T>
	class Numeric : public ValueType
	{
	public:
		static const T MaxValue;
		static const T MinValue;

	protected:
		static Type& GetTypeInternal()
		{
			static Type t(TypeInfo::Struct, internal::NumericFormat<T>::NAME, typeof<ValueType>(), &RegisterType);
			return t;
		}

		static void RegisterType()
		{			
		}

		template<typename U = T>friend const Type* typeof();
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

#define UUT_NUMERIC(type) \
	namespace internal { template<>const char* NumericFormat<type>::NAME = #type; } \
	template<> static const Type* typeof<type>() { return typeof<Numeric<type>>(); }

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
}