#include "Level.h"
#include "Tileset.h"
#include "Entity.h"

namespace uut
{
	Level::Level(Tileset* tileset)
		: _tileset(tileset)
	{
	}

	void Level::PlaceEntity(Entity* entity, const IntVector2& position)
	{
		if (entity == nullptr || entity->_level != nullptr)
			return;

		entity->SetPosition(position);
		entity->_level = this;
		_entities.Add(SharedPtr<Entity>(entity));
	}

	Entity* Level::GetEntityAt(const IntVector2& index) const
	{
		for (uint i = 0; i < _entities.Count(); i++)
		{
			if (_entities[i]->GetPosition() == index)
				return _entities[i];
		}

		return nullptr;
	}

	void Level::Update(float deltaTime)
	{
		for (auto& entity : _entities)
			entity->Update(deltaTime);
	}
}