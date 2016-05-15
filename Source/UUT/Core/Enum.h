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
		explicit EnumValue(int value) { _value = value; };
		explicit EnumValue(T value) { _value = static_cast<int>(value); }

		operator T () const { return static_cast<T>(_value); }

		String ToString() const { return EnumValueBase::ToString(GetType()); }

		bool operator == (T other) const { return static_cast<T>(_value) == other; }
		bool operator != (T other) const { return static_cast<T>(_value) != other; }

		constexpr static T DefaultValue = static_cast<T>(0);

		static const EnumValue<T> Default;
	};

	template<typename T> const EnumValue<T> EnumValue<T>::Default(DefaultValue);


#define UUT_ENUM(type) \
	template<> static const Type* typeof<type>() \
	{ return typeof<EnumValue<type>>(); } \
	template<> constexpr static const type& GetDefault<type>() \
	{ return EnumValue<type>::DefaultValue; } 

#define UUT_ENUM_IMPLEMENT(type) UUT_STRUCT_IMPLEMENT(EnumValue<type>)

#define UUT_REGISTER_ENUM(type) UUT_REGISTER_TYPE(TypeInfo::Enum, EnumValue<type>, #type)
}