#pragma once
#include <Core/Ptr.h>
#include <Core/Collections/List.h>
#include <Core/Collections/HashSet.h>
#include <Core/Delegate.h>
#include "EntityMatcher.h"

namespace uut
{
	class EntityPool;
	class Entity;

	class EntityGroup
	{
	public:
		typedef Delegate<const SharedPtr<Entity>&> EntityCallback;

		 EntityGroup(const EntityMatcher& matcher);

		size_t Count() const { return _entities.Count(); }

		const HashSet<SharedPtr<Entity>>& GetEntities() const { return _entities; }
		const EntityMatcher& GetMatcher() const { return _matcher; }

		EntityCallback onAdd;
		EntityCallback onUpdate;
		EntityCallback onRemove;

	protected:
		EntityPool* _pool;
		EntityMatcher _matcher;
		HashSet<SharedPtr<Entity>> _entities;

		void EntityChanged(const SharedPtr<Entity>& entity);

		friend class EntityPool;
	};
}