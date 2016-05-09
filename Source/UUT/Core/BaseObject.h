#pragma once
#include <Core/Reflection/Type.h>

namespace uut
{
	class BaseObject
	{
		UUT_TYPE(BaseObject, BaseObject)
	public:
		constexpr BaseObject() {}
	};
}