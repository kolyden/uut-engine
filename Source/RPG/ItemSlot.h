#pragma once
#include <Core/Object.h>
#include <Core/HashString.h>

namespace uut { namespace rpg
{

	class ItemSlot : public Object
	{
		UUT_OBJECT(ItemSlot, Object)
	public:
		ItemSlot();

	protected:
		HashString _name;
	};

}}