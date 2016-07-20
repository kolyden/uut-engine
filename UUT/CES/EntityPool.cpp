#include "EntityPool.h"
#include "Entity.h"
#include "EntityMatcher.h"
#include "EntityGroup.h"

namespace uut
{
	SharedPtr<Entity> EntityPool::CreateEntity()
	{
		auto entity = SharedPtr<Entity>(new Entity(&_componentsPool));
		_entities << entity;
		return entity;
	}

	void EntityPool::Update(float deltaTime)
	{
		for (auto& system : _systems)
			system->Update(deltaTime);
	}

	void EntityPool::Render()
	{
		for (auto& system : _systems)
			system->Render();
	}

	void EntityPool::AddSystem(const SharedPtr<EntitySystem>& system)
	{
		if (!system || system->_pool != nullptr)
			return;

		system->_pool = this;
		system->Init();
		_systems << system;
	}

	SharedPtr<EntityGroup> EntityPool::AddGroup(const EntityMatcher& matcher)
	{
		auto group = SharedPtr<EntityGroup>::Make(matcher);
		group->_pool = this;
		_groups << group;
		for (auto& ent : _entities)
			group->EntityChanged(ent);

		return group;
	}

	List<SharedPtr<Entity>> EntityPool::GetEntities(const EntityMatcher& matcher) const
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