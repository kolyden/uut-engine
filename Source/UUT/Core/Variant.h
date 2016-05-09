#pragma once
#include <Core/Collections/List.h>
#include <Core/Reflection/Type.h>
#include <Core/ValueType.h>
#include <Core/Object.h>
#include <Core/Numeric.h>
#include <Core/Enum.h>

namespace uut
{
	class Object;

	enum class VariantType
	{
		Empty,
		Type,
		Numeric,
		Enum,
		Struct,
		Object,
	};

	class Variant
	{
	public:
		Variant();
		explicit Variant(const Type* type);

		// FUNDAMENTAL
		template<typename T, std::enable_if_t<std::is_fundamental<T>::value>* = nullptr>
		explicit Variant(T value)
		{
			SetStruct(typeof<Numeric<T>>(), Numeric<T>(value), sizeof(Numeric<T>));
			_type = VariantType::Numeric;
		}

		// ENUM
		template<typename T, std::enable_if_t<std::is_enum<T>::value>* = nullptr>
		explicit Variant(T value)
		{
			SetStruct(typeof<EnumValue<T>>(), EnumValue<T>(value), sizeof(EnumValue<T>));
			_type = VariantType::Enum;
		}

		// STRUCT
		template<typename T, std::enable_if_t<std::is_base_of<ValueType, T>::value>* = nullptr>
		explicit Variant(const T& value)
		{
			SetStruct(typeof<T>(), value, sizeof(T));
		}

		// OBJECT
		template<typename T, std::enable_if_t < std::is_base_of<Object, T>::value>* = nullptr >
		explicit Variant(T* value)
		{
			SetObject(typeof<T>(), value);
		}

		template<typename T>
		explicit Variant(SharedPtr<T>& value)
		{
			SetObject(typeof<T>(), value);
		}

		template<typename T>
		explicit Variant(WeakPtr<T>& value)
		{
			SetObject(typeof<T>(), value);
		}

		~Variant();

		void Clear();
		bool IsEmpty() const { return _type == VariantType::Empty; }
		bool IsType() const { return _type == VariantType::Type; }
		bool IsNumeric() const { return _type == VariantType::Numeric; }
		bool IsEnum() const { return _type == VariantType::Enum; }
		bool IsValueType() const { return _type == VariantType::Struct || IsEnum() || IsNumeric(); }
		bool IsObject() const { return _type == VariantType::Object; }

		const ValueType* GetStruct(const Type* type) const;
		template<class C>const C* GetStruct() const { return static_cast<const C*>(GetStruct(typeof<C>())); }

		Object* GetObject() const;
		Object* GetObject(const Type* type) const;
		template<class C>C* GetObject() const { return static_cast<C*>(GetObject(typeof<C>())); }

		const Type* GetType() const { return _dataType; }

		// FUNDAMETNAL - NUMERIC
		template<class C, class = typename std::enable_if<std::is_fundamental<C>::value>::type>
		C Get() const
		{
			const Numeric<C>* data = GetStruct<Numeric<C>>();
			return data != nullptr ? *data : Numeric<C>::Zero;
		}

		// ENUM
		template<class C, std::enable_if_t<std::is_enum<C>::value>* = nullptr>
		C Get() const
		{
			auto data = GetStruct<EnumValue<C>>();
			return data != nullptr ? *data : EnumValue<C>::DefaultValue;
		}

		// VALUETYPE - STRUCT
		template<class C, std::enable_if_t<std::is_base_of<ValueType, C>::value>* = nullptr>
		C Get(const C& defaultType = GetDefault<C>()) const
		{
			const C* data = static_cast<const C*>(GetStruct(typeof<C>()));
			return data != nullptr ? *data : defaultType;
		}

		// OBJECT
		template<class C, std::enable_if_t<std::is_base_of<Object, C>::value>* = nullptr>
		C* Get() const { return static_cast<C*>(GetObject(typeof<C>())); }

		template<class C, std::enable_if_t<std::is_base_of<Object, C>::value>* = nullptr>
		SharedPtr<C> GetShared() const
		{
			if (!IsObject()) return SharedPtr<C>::Empty;
			return DynamicCast<C>(_shared);
		}

		static const Variant Empty;

	protected:
		VariantType _type;
		const Type* _dataType;
		std::vector<uint8_t> _data;
		SharedPtr<Object> _shared;

		void SetStruct(const Type* type, const ValueType& value, uint size);
		void SetObject(const Type* type, Object* value);
	};

	template<> constexpr static const Variant& GetDefault<Variant>()
	{
		return Variant::Empty;
	}
}