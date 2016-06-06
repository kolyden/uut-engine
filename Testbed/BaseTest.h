#pragma once
#include <Core/Object.h>

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
		SharedPtr<Graphics> _graphics;
		WeakPtr<ResourceCache> _cache;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() const {}
	};
}
