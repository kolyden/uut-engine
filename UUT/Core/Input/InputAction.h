#pragma once
#include <Core/ValueType.h>
#include <Core/HashString.h>
#include "InputDevice.h"

namespace uut
{
	class InputAction : public ValueType
	{
		UUT_VALUETYPE(uut, InputAction, ValueType)
	public:

	protected:
		HashString _name;
		InputControlType _type;
	};
}