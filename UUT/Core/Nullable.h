#pragma once
#include "ValueType.h"

namespace uut
{
	class Nullable : public ValueType
	{
		UUT_STRUCT(Nullable, ValueType)
	public:
		Nullable() : _dataType(nullptr) {}

		bool HasValue() const { return _dataType != nullptr; }

		ValueType* GetValue();
		const ValueType* GetValue() const;

		// VALUETYPE - STRUCT
		template<class C, std::enable_if_t<std::is_base_of<ValueType, C>::value>* = nullptr>
		bool TryGet(C& value) const
		{
			return TryGetValue(typeof<C>(), value);
		}

	protected:
		const Type* _dataType;
		std::vector<uint8_t> _data;

		bool TryGetValue(const Type* type, ValueType& value) const;
	};
}