#pragma once
#include <Core/String.h>
#include <Core/ValueType.h>
#include <Core/Collections/Dictionary.h>

namespace uut
{
	class EnumValue : public ValueType
	{
		UUT_VALUETYPE(uut, EnumValue, ValueType)
	public:
		explicit constexpr EnumValue(int value) : _value(value) {}

		void SetFlag(int value);
		int GetValue() const;

	protected:
		int _value;
	};

	//////////////////////////////////////////////////////////////////////////////
	template<class T
		, class = typename std::enable_if<std::is_enum<T>::value, void>::type>
		struct Enum
	{
		static_assert(std::is_enum<T>::value, "Expected enum type");
		static const char* Name;
		static const bool IsFlag;

		static size_t Count() { return Values.Count(); }
		static const Dictionary<T, String>& GetNames() { return Names; }
		static const List<T>& GetValues() { return Values; }

		static String ToString(T value)
		{
			auto it = Names.Find(value);
			return it != Names.End() ? it->second : std::to_string((int)value);
		}

		static T Parse(const String& name, T defaultValue)
		{
			T value;
			if (!TryParse(name, value))
				value = defaultValue;

			return value;
		}

		static bool TryParse(const String& name, T& value)
		{
			for (auto& it : Names)
			{
				if (it.second == name)
				{
					value = it.first;
					return true;
				}
			}

			return false;
		}

	private:
		static Dictionary<T, String> Names;
		static List<T> Values;

		template<class U = T>
		friend class EnumValueImpl;
	};

	//////////////////////////////////////////////////////////////////////////////
	template<class T>
	class EnumValueImpl : public EnumValue
	{
	public:
		typedef T EnumType;

		constexpr EnumValueImpl() : EnumValue(0) {}
		constexpr EnumValueImpl(T value) : EnumValue(static_cast<int>(value)) {}

		operator T () const { return static_cast<T>(_value); }

		String ToString() const
		{
			auto it = Enum<T>::Names.find(static_cast<T>(_value));
			if (it != Enum<T>::Names.end())
				return it->second;

			return TypeOf<T>()->GetName() + "(" + std::to_string(_value) + ")";
		}

	protected:
		template<typename... Args,
			class = typename std::enable_if<sizeof...(Args) % 2 == 0, void>::type>
			static void RegisterValues(Args&&... args)
		{
			_internalRegisterRecurse<0, Args...>(std::tuple<Args...>(args...));
		}

		static String ToStringStatic(T value)
		{
			auto it = Enum<T>::Names.Find(value);
			if (it != Enum<T>::Names.End())
				return it->second;

			return std::to_string(static_cast<int>(value));
		}

	private:
		template<size_t index, typename... Args,
			std::enable_if_t<(index < sizeof...(Args)), void>* = nullptr>
			static void _internalRegisterRecurse(const std::tuple<Args...>& args)
		{
			_internalTupleSetName<index, Args...>(args);
			_internalTupleSetValue<index + 1, Args...>(args);

			_internalRegisterRecurse<index + 2, Args...>(args);
		}

		template<size_t index, typename... Args,
			std::enable_if_t<(index >= sizeof...(Args)), void>* = nullptr>
			static void _internalRegisterRecurse(const std::tuple<Args...>& args)
		{
		}

		template<int index, typename... Args>
		static void _internalTupleSetValue(const std::tuple<Args...>& args)
		{
			// 			static_assert(is_convertible<typename tuple_element<index, tuple<Args...>>::type, T>::value,
			// 				"expect enum value");
			Enum<T>::Values.Add(std::get<index>(args));
		}

		template<int index, typename... Args>
		static void _internalTupleSetName(const std::tuple<Args...>& args)
		{
			Enum<T>::Names[std::get<index + 1>(args)] = std::get<index>(args);
		}
	};

	namespace detail {
		template<class T>
		struct Enum {};
	}

#define UUT_ENUM(library, type) \
	class type##Enum : public EnumValueImpl<type> { \
		UUT_BASETYPE(library, type##Enum, EnumValue) \
	public: \
		constexpr type##Enum() : EnumValueImpl<type>() {} \
		constexpr type##Enum(type value) : EnumValueImpl<type>(value) {} \
		type##Enum& operator = (type value) { _value = (int)value; return *this; } \
	}; \
	namespace detail { \
	template<> struct Enum<type> { typedef type##Enum TYPE; }; } \
	UUT_DEFAULT_VALUE(type, (type)0); \
	UUT_TYPEOF_VALUE(type, type##Enum)

#define UUT_ENUM_IMPLEMENT(type) \
	const char* Enum<type>::Name = #type; \
	const bool Enum<type>::IsFlag = false; \
	template<> Dictionary<type, String> Enum<type>::Names; \
	List<type> Enum<type>::Values; \
	UUT_BASETYPE_IMPLEMENT(type##Enum)

#define UUT_REGISTER_ENUM(type) \
	UUT_REGISTER_OBJECT(type##Enum)
}