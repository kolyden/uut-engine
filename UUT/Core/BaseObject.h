#pragma once
#include <Core/Reflection/Type.h>

namespace uut
{
	class BaseObject
	{
		UUT_BASETYPE(BaseObject, BaseObject)
	public:
		constexpr BaseObject() {}
	};
}