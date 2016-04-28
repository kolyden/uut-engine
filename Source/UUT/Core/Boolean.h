#pragma once
#include "ValueType.h"
#include <Core/HashString.h>

namespace uut
{
	class Boolean : public ValueType
	{
		UUT_STRUCT(Boolean, ValueType)
	public:
		static const Boolean True;
		static const Boolean False;
		static const HashString TrueHash;
		static const HashString FalseHash;
	};

// 	template<>
// 	static const Type* typeof<bool>()
// 	{
// 		return typeof<Boolean>();
// 	}
}