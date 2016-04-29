#pragma once
#include <Core/String.h>
#include <Core/ValueType.h>

namespace uut
{
	class Type;

	class EnumValueBase : public ValueType
	{
		UUT_TYPE(EnumValueBase, ValueType)
	public:
		EnumValueBase();

		int GetData() const { return _value; }

		static const EnumValueBase Empty;

	protected:
		int _value;

		String ToString(const Type* type) const;
	};

	template<typename T>
	class EnumValue : public EnumValueBase
	{
		UUT_TYPE(EnumValue, EnumValueBase)
	public:
		typedef T EnumType;

		EnumValue() {};
		explicit EnumValue(T value) { _value = (int)value; }

		operator T () const { return (T)_value; }

		String ToString() const { return EnumValueBase::ToString(GetType()); }

		bool operator == (T other) const { return (T)_value == other; }
		bool operator != (T other) const { return (T)_value != other; }

		static const T Default;

		static const EnumValue<T> Empty;
	};

	template<typename T> const T EnumValue<T>::Default = static_cast<T>(0);
	template<typename T> const EnumValue<T> EnumValue<T>::Empty(Default);


#define UUT_ENUM(type) \
	template<> static const Type* typeof<type>() \
	{ return typeof<EnumValue<type>>(); }

#define UUT_ENUM_IMPLEMENT(type) UUT_STRUCT_IMPLEMENT(EnumValue<type>)

#define UUT_REGISTER_ENUM(type) UUT_REGISTER_TYPE(TypeInfo::Enum, EnumValue<type>, #type)
}