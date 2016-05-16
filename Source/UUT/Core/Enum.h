#pragma once
#include <Core/String.h>
#include <Core/ValueType.h>

namespace uut
{
	class Type;

	class Enum : public ValueType
	{
		UUT_TYPE(Enum, ValueType)
	public:
		constexpr Enum() : _value(0) {}
		constexpr explicit Enum(int value) : _value(value) {}

		int GetData() const { return _value; }

		static const Enum Default;

	protected:
		int _value;

		String ToString(const Type* type) const;
	};

	template<typename T>
	class EnumValue : public Enum
	{
	public:
		typedef T EnumType;

		EnumValue() {};
		explicit EnumValue(int value) { _value = value; };
		explicit EnumValue(T value) { _value = static_cast<int>(value); }

		operator T () const { return static_cast<T>(_value); }

		String ToString() const { return Enum::ToString(T::GetTypeStatic()); }

		bool operator == (T other) const { return static_cast<T>(_value) == other; }
		bool operator != (T other) const { return static_cast<T>(_value) != other; }

		constexpr static T DefaultValue = static_cast<T>(0);

		static const EnumValue<T> Default;
	};

	template<typename T> const EnumValue<T> EnumValue<T>::Default(DefaultValue);
}