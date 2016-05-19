#pragma once
#include <Core/Collections/List.h>
#include <Core/Reflection/Type.h>
#include <Core/ValueType.h>
#include <Core/Object.h>
#include <Core/Boolean.h>
#include <Core/Char.h>
#include <Core/Numeric.h>
#include <Core/Enum.h>
#include <Core/Single.h>
#include <Core/Double.h>

namespace uut
{
	class Object;

	enum class VariantType
	{
		Empty,
		Type,
		Fundamental,
		Enum,
		Struct,
		Object,
	};

	class Variant
	{
	public:
		Variant();
		Variant(const Type* type);

		// FUNDAMENTAL
		template<typename T, std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
		Variant(T value)
		{
			SetStruct(typeof<typename detail::Fundamental<T>::TYPE>(),
				detail::Fundamental<T>::TYPE(value),
				sizeof(detail::Fundamental<T>::TYPE));
			_type = VariantType::Fundamental;
		}

		// ENUM
		template<typename T, std::enable_if_t<std::is_enum<T>::value>* = nullptr>
		Variant(T value)
		{
			SetStruct(typeof<typename detail::Enum<T>::TYPE>(),
				detail::Enum<T>::TYPE(value),
				sizeof(detail::Enum<T>::TYPE));
			_type = VariantType::Enum;
		}

		// STRUCT
		template<typename T, std::enable_if_t<std::is_base_of<ValueType, T>::value>* = nullptr>
		Variant(const T& value)
		{
			SetStruct(typeof<T>(), value, sizeof(T));
		}

		Variant(const Type* type, const ValueType& value)
		{
			SetStruct(type, value, type->GetSize());
		}

		// OBJECT
		template<typename T, std::enable_if_t < std::is_base_of<Object, T>::value>* = nullptr >
		Variant(T* value)
		{
			SetObject(typeof<T>(), value);
		}

		template<typename T>
		Variant(SharedPtr<T>& value)
		{
			SetObject(typeof<T>(), value);
		}

		template<typename T>
		Variant(WeakPtr<T>& value)
		{
			SetObject(typeof<T>(), value);
		}

		~Variant();

		void Clear();
		bool IsEmpty() const { return _type == VariantType::Empty; }
		bool IsType() const { return _type == VariantType::Type; }
		bool IsNumeric() const { return _type == VariantType::Fundamental; }
		bool IsEnum() const { return _type == VariantType::Enum; }
		bool IsValueType() const { return _type == VariantType::Struct || IsEnum() || IsNumeric(); }
		bool IsObject() const { return _type == VariantType::Object; }

		const ValueType* GetStruct(const Type* type) const;
		template<class C>const C* GetStruct() const { return static_cast<const C*>(GetStruct(typeof<C>())); }		

		Object* GetObject() const;
		Object* GetObject(const Type* type) const;
		template<class C>C* GetObject() const { return static_cast<C*>(GetObject(typeof<C>())); }

		const Type* GetType() const { return _dataType; }

		// TYPE
		template<class C, std::enable_if_t<std::is_base_of<Type, 
			std::remove_pointer_t<std::remove_const_t<C>>>::value>* = nullptr>
		const Type* Get() const
		{
			return _dataType;
		}

		// FUNDAMETNAL - NUMERIC
		template<class C, class = typename std::enable_if<std::is_fundamental<C>::value>::type>
		C Get(C defaultValue = typename detail::Fundamental<C>::TYPE::DefaultValue) const
		{
			auto data = GetStruct<typename detail::Fundamental<C>::TYPE>();
			if (data != nullptr)
				return *data;

			typename detail::Fundamental<C>::TYPE value;
			if (TryCastStruct(value))
				return value;
			
			return defaultValue;
		}

		// ENUM
		template<class C, std::enable_if_t<std::is_enum<C>::value>* = nullptr>
		C Get(C defaultValue = GetDefault<C>()) const
		{
			auto data = GetStruct<typename detail::Enum<C>::TYPE>();
			if (data != nullptr)
				return *data;

			typename detail::Enum<C>::TYPE value;
			if (TryCastStruct(value))
				return value;

			return defaultValue;
		}

		// VALUETYPE - STRUCT
		template<class C, std::enable_if_t<std::is_base_of<ValueType, C>::value>* = nullptr>
		C Get(const C& defaultValue = GetDefault<C>()) const
		{
			const C* data = static_cast<const C*>(GetStruct(typeof<C>()));
			if (data != nullptr)
				return *data;

			C value;
			if (TryCastStruct(value))
				return value;

			return defaultValue;
		}

		// OBJECT
		template<class C, std::enable_if_t<std::is_base_of<Object, C>::value>* = nullptr>
		C* Get() const { return static_cast<C*>(GetObject(typeof<C>())); }

		// FUNDAMETNAL - NUMERIC
		template<class C, class = typename std::enable_if<std::is_fundamental<C>::value>::type>
		bool TryGet(C& value) const
		{
			auto data = GetStruct<typename detail::Fundamental<C>::TYPE>();
			if (data == nullptr)
			{
				value = *data;
				return true;
			}

			typename detail::Fundamental<C>::TYPE numeric;
			if (TryCastStruct(numeric))
			{
				value = numeric;
				return true;
			}

			return false;
		}

		// ENUM
		template<class C, std::enable_if_t<std::is_enum<C>::value>* = nullptr>
		bool TryGet(C& value) const
		{
			auto data = GetStruct<typename detail::Enum<C>::TYPE>();
			if (data != nullptr)
			{
				value = *data;
				return true;
			}

			typename detail::Enum<C>::TYPE enumValue;
			if (TryCastStruct(enumValue))
			{
				value = enumValue;
				return true;
			}

			return false;
		}

		// VALUETYPE - STRUCT
		template<class C, std::enable_if_t<std::is_base_of<ValueType, C>::value>* = nullptr>
		bool TryGet(C& value) const
		{
			const C* data = static_cast<const C*>(GetStruct(typeof<C>()));
			if (data != nullptr)
			{
				value = *data;
				return true;
			}				

			return TryCastStruct(typeof<C>(), value);
		}

		// OBJECT
		template<class C, std::enable_if_t<std::is_base_of<Object, C>::value>* = nullptr>
		bool TryGet(C** value) const
		{
			auto obj = static_cast<C*>(GetObject(typeof<C>()));
			if (obj == nullptr)
				return false;

			*value = obj;
			return true;
		}

		static const Variant Empty;

	protected:
		VariantType _type;
		const Type* _dataType;
		std::vector<uint8_t> _data;
		SharedPtr<Object> _shared;

		bool TryCastStruct(const Type* type, ValueType& value) const;
		template<class C>bool TryCastStruct(C& value) const { return TryCastStruct(typeof<C>(), value); }

		void SetStruct(const Type* type, const ValueType& value, uint size);
		void SetObject(const Type* type, Object* value);
	};

	template<> static constexpr const Variant& GetDefault<Variant>()
	{
		return Variant::Empty;
	}
}