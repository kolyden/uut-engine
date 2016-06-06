#include "Nullable.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(Nullable)
	{}

	ValueType* Nullable::GetValue()
	{
		if (!HasValue())
			return nullptr;

		return reinterpret_cast<ValueType*>(_data.data());
	}

	const ValueType* Nullable::GetValue() const
	{
		if (!HasValue())
			return nullptr;

		return reinterpret_cast<const ValueType*>(_data.data());
	}

	bool Nullable::TryGetValue(const Type* type, ValueType& value) const
	{
		auto value_type = reinterpret_cast<const ValueType*>(_data.data());
		if (_dataType == type)
		{
			value = *value_type;
			return true;
		}

		if (_dataType->Convert(*value_type, type, value))
			return true;

		return false;
	}
}