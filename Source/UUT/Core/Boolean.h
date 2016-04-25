#pragma once
#include "ValueType.h"

namespace uut
{
	class Boolean : public ValueType
	{
		UUT_STRUCT(Boolean, ValueType)
	public:
	};

	template<>
	static const Type* typeof<bool>()
	{
		return typeof<Boolean>();
	}
}