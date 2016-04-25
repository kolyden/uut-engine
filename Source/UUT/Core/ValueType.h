#pragma once
#include <Core/Reflection/Type.h>

namespace uut
{
#define UUT_STRUCT(typeName, parentType) UUT_TYPE(typeName, parentType)
#define UUT_STRUCT_IMPLEMENT(type) UUT_TYPE_IMPLEMENT(type)

	// base object for "struct object" like Vector2 etc.
	// No virtual allowed!
	class ValueType
	{
		UUT_STRUCT(ValueType, ValueType)
	public:
		ValueType();
	};
}