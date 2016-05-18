#pragma once
#include <Core/Object.h>
#include "LevelIndex.h"

namespace uut { namespace rpg
{

	class Entity : public Object
	{
		UUT_OBJECT(Entity, Object)
	public:
		Entity();

		const LevelIndex& GetLevelIndex() const;

	protected:
		LevelIndex _index;
	};

} }