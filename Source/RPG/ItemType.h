#pragma once
#include <Core/HashString.h>
#include <Core/Object.h>

namespace uut { namespace rpg
{

	class ItemType : public Object
	{
		UUT_OBJECT(ItemType, Object)
	public:
		ItemType();

	protected:
		HashString _name;
	};

} }