#pragma once
#include <Core/Object.h>

namespace uut
{
	class EntityPool;

	class EntitySystem : public Object
	{
		UUT_OBJECT(uut, EntitySystem, Object)
	public:
		EntitySystem() : _pool(nullptr) {}
		virtual ~EntitySystem() {}

	protected:
		EntityPool* _pool;

		virtual void Init() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}

		friend class EntityPool;
	};
}