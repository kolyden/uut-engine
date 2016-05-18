#include "Entity.h"

namespace uut { namespace rpg {

	UUT_OBJECT_IMPLEMENT(Entity)
	{}

	Entity::Entity()
	{
	}

	const LevelIndex& Entity::GetLevelIndex() const
	{
		return _index;
	}

} }