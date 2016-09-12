#pragma once
#include <Core/BaseObject.h>

namespace uut
{
#define UUT_VALUETYPE(library, typeName, parentType) \
	UUT_BASETYPE(library, typeName, parentType)

#define UUT_VALUETYPE_IMPLEMENT(type) \
	UUT_BASETYPE_IMPLEMENT(type)

	// base object for "struct object" like Vector2 etc.
	// No virtual allowed!
	class ValueType : public BaseObject
	{
		UUT_VALUETYPE(uut, ValueType, BaseObject)
	public:
		constexpr ValueType() {};
	};
}