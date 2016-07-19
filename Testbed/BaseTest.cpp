#include "BaseTest.h"
#include <Video/Graphics.h>
#include <Resources/ResourceCache.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(BaseTest)
	{
	}

	BaseTest::BaseTest()
	{
	}

	void BaseTest::Update(float deltaTime)
	{
		OnUpdate(deltaTime);
	}

	void BaseTest::Render() const
	{
		OnRender();
		_graphics->Flush();
	}
}