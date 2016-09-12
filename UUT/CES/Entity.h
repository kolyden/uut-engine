#pragma once
#include <Core/Collections/Dictionary.h>
#include <Core/Reflection/Type.h>
#include "Component.h"
#include "EntitySystem.h"
#include <stack>
#include <Core/Object.h>

namespace uut
{
	struct EntityId
	{
		explicit constexpr EntityId(uint16_t val) : value(val) {}

		bool IsValid() const { return value != Invalid.value; }

		uint16_t value;

		bool operator == (const EntityId& other) const { return value == other.value; }
		bool operator != (const EntityId& other) const { return value != other.value; }
		bool operator <= (const EntityId& other) const { return value <= other.value; }
		bool operator >= (const EntityId& other) const { return value >= other.value; }
		bool operator < (const EntityId& other) const { return value < other.value; }
		bool operator > (const EntityId& other) const { return value > other.value; }

		static const EntityId Invalid;

		static EntityId Generate()
		{
			static uint16_t value = 0;
			return EntityId(value++);
		}
	};

	class Entity : public Object
	{
		UUT_OBJECT(uut, Entity, Object)
	public:
		template<class C, typename... Args,
			class = typename std::enable_if<std::is_base_of<Component, C>::value, void>::type>
		SharedPtr<Entity> Add(Args&&... args)
		{			
			AddComponent(TypeOf<C>(), CreateComponent<C>(std::forward<Args>(args)...));
			return GetSharedThis();
		}

		template<class C,
			class = typename std::enable_if<std::is_base_of<Component, C>::value, void>::type>
		SharedPtr<Entity> Remove()
		{
			RemoveComponent(TypeOf<C>());
			return GetSharedThis();
		}

		template<class C, typename... Args>
		SharedPtr<Entity> Replace(Args&&... args)
		{
			ReplaceComponent(TypeOf<C>(), CreateComponent<C>(std::forward<Args>(args)...));
			return GetSharedThis();
		}

		template<class C,
			class = typename std::enable_if<std::is_base_of<Component, C>::value, void>::type>
		const C* Get() const
		{
			return static_cast<const C*>(GetComponent(TypeOf<C>()));
		}

		template<class C,
			class = typename std::enable_if<std::is_base_of<Component, C>::value, void>::type>
		bool Has() const
		{
			return HasComponent(TypeOf<C>());
		}

		bool HasComponents(const List<const Type*>& types) const;
		bool HasAnyComponents(const List<const Type*>& types) const;

		void AddComponent(const Type* type, Component* component);
		void RemoveComponent(const Type* type);
		bool HasComponent(const Type* type) const;
		void ReplaceComponent(const Type* type, Component* component);
		const Component* GetComponent(const Type* type) const;

	protected:
		explicit Entity(Dictionary<const Type*, std::stack<Component*>>* pools);

		template<class C, typename... Args>
		Component* CreateComponent(Args&&... args)
		{
			const auto type = TypeOf<C>();
			auto pool = GetComponentPool(type);

			Component* comp;
			if (!pool->empty())
			{
				comp = pool->top();
				pool->pop();
			}
			else comp = new C();

			((C*)comp)->Reset(std::forward<Args>(args)...);
			return comp;
		}

		std::stack<Component*>* GetComponentPool(const Type* type) const;

		Dictionary<const Type*, Component*> _components;
		Dictionary<const Type*, std::stack<Component*>>* _componentPools;
		friend class EntityPool;
	};

	typedef SharedPtr<Entity> EntityPtr;
}