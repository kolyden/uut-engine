#include "Entity.h"

namespace uut
{

	bool Entity::HasComponents(const List<const Type*>& types) const
	{
		for (auto it : types)
		{
			if (!HasComponent(it))
				return false;
		}

		return true;
	}

	void Entity::AddComponent(const Type* type, Component* component)
	{
		_components[type] = component;
	}

	void Entity::RemoveComponent(const Type* type)
	{
		auto it = _components.Find(type);
		if (it == _components.End())
			return;

		auto pool = GetComponentPool(type);
		pool->push(it->second);
		_components.Remove(it);
	}

	bool Entity::HasComponent(const Type* type) const
	{
		return _components.Contains(type);
	}

	void Entity::ReplaceComponent(const Type* type, Component* component)
	{
		RemoveComponent(type);
		AddComponent(type, component);
	}

	const Component* Entity::GetComponent(const Type* type) const
	{
		auto it = _components.Find(type);
		if (it == _components.End())
			return nullptr;

		return it->second;
	}

	std::stack<Component*>* Entity::GetComponentPool(const Type* type) const
	{
		return &_componentPools->Get(type);
	}
}