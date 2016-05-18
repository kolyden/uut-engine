#pragma once
#include <Core/Collections/List.h>
#include "Item.h"
#include <Core/Ptr.h>

namespace uut { namespace rpg
{

	class ItemContainer
	{
	public:

	protected:
		List<SharedPtr<Item>> _data;
	};

} }
