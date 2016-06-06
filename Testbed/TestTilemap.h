#pragma once
#include "BaseTest.h"
#include <Tilemap/Tilemap.h>

namespace uut
{
	class Player;

	class TestTilemap : public BaseTest
	{
		UUT_OBJECT(TestTilemap, BaseTest)
	public:
		TestTilemap();

	protected:
		SharedPtr<Tilemap> _tilemap;
		WeakPtr<Player> _player;

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender() const override;
	};
}
