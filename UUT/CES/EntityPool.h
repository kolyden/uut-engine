#pragma once
#include <Core/Object.h>
#include <Core/Collections/List.h>
#include <Core/Collections/Dictionary.h>
#include <stack>

namespace uut
{
	class EntityGroup;
	class Component;
	class System;
	class Matcher;
	class Entity;

	class EntityPool : public Object
	{
	public:
		SharedPtr<Entity> CreateEntity();
	
		void AddSystem(const SharedPtr<System>& system);
		SharedPtr<EntityGroup> AddGroup(const SharedPtr<Matcher>& matcher);

		void Execute();

		List<SharedPtr<Entity>> GetEntities(const Matcher& matcher) const;

	protected:
		List<SharedPtr<System>> _systems;
		List<SharedPtr<Entity>> _entities;
		List<SharedPtr<EntityGroup>> _groups;
		Dictionary<const Type*, std::stack<Component*>> _componentsPool;
	};
}