#pragma once
#include <Core/Ptr.h>
#include <Core/Collections/List.h>
#include <Core/Collections/HashSet.h>
#include <Core/Delegate.h>

namespace uut
{
	class EntityPool;
	class Entity;
	class Matcher;

	class EntityGroup
	{
	public:
		typedef Delegate<const SharedPtr<Entity>&> EntityCallback;

		EntityGroup(const SharedPtr<Matcher>& matcher);

		size_t Count() const { return _entities.Count(); }

		const HashSet<SharedPtr<Entity>>& GetEntities() const { return _entities; }
		const SharedPtr<Matcher>& GetMatcher() const;

		EntityCallback onAdd;
		EntityCallback onUpdate;
		EntityCallback onRemove;

	protected:
		EntityPool* _pool;
		SharedPtr<Matcher> _matcher;
		HashSet<SharedPtr<Entity>> _entities;

		void EntityChanged(const SharedPtr<Entity>& entity);

		friend class EntityPool;
	};
}