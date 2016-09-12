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

#define UUT_ENUMFLAG_IMPLEMENT(name, type) \
	const char* Enum<type>::Name = #type; \
	const bool Enum<type>::IsFlag = true; \
	template<> Dictionary<type, String> Enum<type>::Names; \
	List<type> Enum<type>::Values; \
	UUT_VALUETYPE_IMPLEMENT(name)
}