#pragma once
#include <Core/Object.h>
#include <Core/HashString.h>

namespace uut { namespace rpg
{

	class ItemType;

	class Item : public Object
	{
		UUT_OBJECT(Item, Object)
	public:
		Item();

	protected:
		SharedPtr<ItemType> _itemType;
	};

} }