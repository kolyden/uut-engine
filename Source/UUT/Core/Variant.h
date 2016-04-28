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
		//Numeric, ?? - no destructor needed
		Struct,
		Object,
	};

	class Variant
	{
	public:
		Variant();

		// FUNDAMENTAL
		template<typename T, class = typename std::enable_if<std::is_fundamental<T>::value>::type>
		explicit Variant(T value)
		{
			SetStruct(typeof<Numeric<T>>(), Numeric<T>(value), sizeof(Numeric<T>));
		}

		// ENUM
// 		template<typename T, class = typename std::enable_if<std::is_enum<T>::value>::type>
// 		explicit Variant(T value)
// 		{
// 			SetStruct(typeof<EnumValue<T>>(), EnumValue<T>(value), sizeof(EnumValue<T>));
// 		}

		// STRUCT
		template<typename T, class = typename std::enable_if<std::is_base_of<ValueType, T>::value>::type>
		explicit Variant(const T& value)
		{
			SetStruct(typeof<T>(), value, sizeof(T));
		}

		// OBJECT
		template<typename T, class = typename std::enable_if<std::is_base_of<Object, T>::value>::type>
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
		bool IsEmpty() const { return _dataType == nullptr; }

		const ValueType* GetStruct(const Type* type) const;
		template<class C>const C* GetStruct() const { return static_cast<const C*>(GetStruct(typeof<C>())); }

		Object* GetObject(const Type* type) const;
		template<class C>C* GetObject() const { return static_cast<C*>(GetObject(typeof<C>())); }

		template<typename T>
		T GetNumeric()
		{
			auto data = GetStruct<Numeric<T>>();
			return data != nullptr ? *data : 0;
		}

		// FUNDAMETNAL - NUMERIC
		template<class C, class = typename std::enable_if<std::is_fundamental<C>::value>::type>
		C Get() const
		{
			const Numeric<C>* data = GetStruct<Numeric<C>>();
			return data != nullptr ? *data : Numeric<C>::Zero;
		}

		// VALUETYPE - STRUCT
		template<class C, class = typename std::enable_if<std::is_base_of<ValueType, C>::value>::type>
		C Get(const C& defaultType) const
		{
			const C* data = static_cast<const C*>(GetStruct(typeof<C>()));
			return data != nullptr ? *data : defaultType;
		}

		// OBJECT
		template<class C, class = typename std::enable_if<std::is_base_of<Object, C>::value>::type>
		C* Get() const { return static_cast<C*>(GetObject(typeof<C>())); }

		static const Variant Empty;

	protected:
		VariantType _type;
		const Type* _dataType;
		std::vector<uint8_t> _data;
		SharedPtr<Object> _shared;

		void SetStruct(const Type* type, const ValueType& value, uint size);
		void SetObject(const Type* type, Object* value);
	};
}