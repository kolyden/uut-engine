#include "EntityPool.h"
#include "Entity.h"
#include "Matcher.h"
#include "EntityGroup.h"

namespace uut
{
	SharedPtr<Entity> EntityPool::CreateEntity()
	{
		auto entity = SharedPtr<Entity>(new Entity(&_componentsPool));
		_entities << entity;
		return entity;
	}

	void EntityPool::Execute()
	{
		for (auto& system : _systems)
			system->Execute();
	}

	void EntityPool::AddSystem(const SharedPtr<System>& system)
	{
		if (!system || system->_pool != nullptr)
			return;

		system->_pool = this;
		system->Init();
		_systems << system;
	}

	SharedPtr<EntityGroup> EntityPool::AddGroup(const Matcher& matcher)
	{
		auto group = SharedPtr<EntityGroup>::Make(matcher);
		group->_pool = this;
		_groups << group;
		for (auto& ent : _entities)
			group->EntityChanged(ent);

		return group;
	}

	List<SharedPtr<Entity>> EntityPool::GetEntities(const Matcher& matcher) const
	{
		List<EntityPtr> list;
		for (auto& entity : _entities)
		{
			if (matcher.Matches(entity))
				list << entity;
		}
		return list;
	}
}