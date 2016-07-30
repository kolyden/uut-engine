#pragma once
#include <Core/Object.h>
#include <Core/Collections/List.h>
#include <Core/Collections/Dictionary.h>
#include <stack>

namespace uut
{
	class EntityGroup;
	class Component;
	class EntitySystem;
	class EntityMatcher;
	class Entity;

	class EntityPool : public Object
	{
	public:
		SharedPtr<Entity> CreateEntity();
	
		void AddSystem(const SharedPtr<EntitySystem>& system);
		SharedPtr<EntityGroup> AddGroup(const EntityMatcher& matcher);

		template<class T, typename... Args,
			class = typename std::enable_if<std::is_base_of<EntitySystem, T>::value, void>::type,
			class = typename std::enable_if<std::is_constructible<T, Args...>::value, void>::type>
		SharedPtr<T> CreateSystem(Args&&... args)
		{
			auto system = MakeShared<T>(std::forward<Args>(args)...);
			AddSystem(system);
			return system;
		}

		void Update(float deltaTime);
		void Render();

		List<SharedPtr<Entity>> GetEntities(const EntityMatcher& matcher) const;

	protected:
		List<SharedPtr<EntitySystem>> _systems;
		List<SharedPtr<Entity>> _entities;
		List<SharedPtr<EntityGroup>> _groups;
		Dictionary<const Type*, std::stack<Component*>> _componentsPool;
	};
}