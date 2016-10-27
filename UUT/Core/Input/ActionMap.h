#pragma once
#include <Resources/Resource.h>
#include "InputAction.h"

namespace uut
{
	class ActionMap : public Resource
	{
		UUT_OBJECT(uut, ActionMap, Resource)
	public:

	protected:
		List<InputAction> _actions;
	};
}