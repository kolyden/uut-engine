#pragma once
#include "Enum.h"

namespace uut
{
	template<class T>
	class EnumFlagsImpl : public EnumValueImpl<T>
	{
	public:
		constexpr EnumFlagsImpl() {}
		constexpr EnumFlagsImpl(int value) : EnumValueImpl<T>(static_cast<T>(value)) {}
		constexpr EnumFlagsImpl(T value) : EnumValueImpl<T>(value) {}

		void SetFlag(T value, bool isSet)
		{
			isSet ? SetFlag(value) : ClearFlag(value);
		}

		void SetFlag(T value)
		{
			EnumValueImpl<T>::_value = EnumValueImpl<T>::_value | static_cast<int>(value);
		}

		void ClearFlag(T value)
		{
			EnumValueImpl<T>::_value = EnumValueImpl<T>::_value & ~static_cast<int>(value);
		}

		void ToggleFlag(T value)
		{
			HasFlag(value) ? ClearFlag(value) : SetFlag(value);
		}

		bool HasFlag(T value) const
		{
			return (EnumValueImpl<T>::_value & static_cast<int>(value)) == static_cast<int>(value);
		}

		String ToString() const
		{
			String out;
			for (T val : Enum<T>::GetValues())
			{
				if (!HasFlag(val))
					continue;

				if (!out.IsEmpty())
					out += "|";

				out += ToStringStatic(val);
			}

			return out;
		}
	};

#define UUT_ENUMFLAG(library, name, type) \
	class name : public EnumFlagsImpl<type> { \
		UUT_VALUETYPE(library, name, EnumValue) \
	public: \
		constexpr name() : EnumFlagsImpl<type>() {} \
		constexpr name(type value) : EnumFlagsImpl<type>(value) {} \
		constexpr name(int value) : EnumFlagsImpl<type>(value) {} \
		static const char* GetEnumName() { return #type; } \
		name& operator = (type value) { _value = (int)value; return *this; } \
		name& operator |= (type value) { _value |= (int)value; return *this; } \
	}; \
	namespace detail { \
	template<> struct Enum<type> { typedef name TYPE; }; } \
	UUT_DEFAULT(type, (type)0); \
	UUT_VALUE_TYPE(type, name) \
	static name operator| (name::EnumType a, name::EnumType b) { \
		return name(static_cast<int>(a) | static_cast<int>(b)); \
	}

#define UUT_ENUMFLAG_IMPLEMENT(name) \
	const char* Enum<name::EnumType>::Name = name::GetEnumName(); \
	const bool Enum<name::EnumType>::IsFlag = true; \
	template<> Dictionary<name::EnumType, String> Enum<name::EnumType>::Names; \
	List<name::EnumType> Enum<name::EnumType>::Values; \
	UUT_VALUETYPE_IMPLEMENT(name)
}