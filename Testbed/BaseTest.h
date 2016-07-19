#pragma once
#include <Core/Object.h>
#include <Core/Module.h>

namespace uut
{
	class Graphics;
	class ResourceCache;

	class BaseTest : public Object
	{
		UUT_OBJECT(BaseTest, Object)
	public:
		BaseTest();

		virtual void Update(float deltaTime);
		virtual void Render() const;

	protected:
		ModuleInstance<Graphics> _graphics;
		ModuleInstance<ResourceCache> _cache;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() const {}
	};
}
