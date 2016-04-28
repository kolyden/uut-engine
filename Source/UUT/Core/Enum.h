#pragma once
#include <Core/String.h>
#include <Core/ValueType.h>

namespace uut
{
	class Type;

	template<typename T>
	class EnumValue : public ValueType
	{
		UUT_TYPE(EnumValue, ValueType)
	public:
		EnumValue() : _value(Default) {};
		explicit EnumValue(T value) : _value(value) {}

		String ToString() const
		{
			return String::Empty;
		}

		static String ToString(T value)
		{
			return String::Empty;
		}

		static bool TryParse(const String& str, T& value)
		{
			return false;
		}

		bool operator == (T other) const { return _value == other; }
		bool operator != (T other) const { return _value != other; }

		static const T Default;

	protected:
		T _value;
	};

	template<typename T> const T EnumValue<T>::Default = 0;


#define UUT_ENUM(type) \
	template<> static const Type* typeof<type>() \
	{ return typeof<Numeric<type>>(); }

#define UUT_ENUM_IMPLEMENT(type)
}