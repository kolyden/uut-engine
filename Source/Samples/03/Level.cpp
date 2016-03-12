#include "Level.h"
#include "LevelChunk.h"
#include <Core/Math/Math.h>
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
		if (entity == nullptr)
			return;

		entity->SetPosition(position);
		_entities.Add(SharedPtr<Entity>(entity));
	}

	void Level::Update(float deltaTime)
	{
		_tileset->Update(deltaTime);
		for (auto& it : _chunks)
			it.second->Update(deltaTime);

		for (auto& entity : _entities)
			entity->Update(deltaTime);
	}

	void Level::Draw(Graphics* graphics) const
	{
		if (graphics == nullptr)
			return;

		for (auto& it : _chunks)
			it.second->Draw(graphics);

		for (int i = 0; i < _entities.Count(); i++)
			_entities[i]->Draw(graphics);
	}

	LevelChunk* Level::FindChunk(const IntVector2& index) const
	{
		auto it = _chunks.Find(index);
		return it != _chunks.End() ? it->second.Get() : nullptr;
	}

	LevelChunk* Level::GetChunk(const IntVector2& index)
	{
		auto chunk = FindChunk(index);
		if (chunk)
			return chunk;

		chunk = new LevelChunk(this, index);
		_chunks[index] = chunk;
		return chunk;
	}

	LevelChunk* Level::FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const
	{
		const IntVector2 index(
			Math::Div(worldPos.x, LevelChunk::COUNT).quot,
			Math::Div(worldPos.y, LevelChunk::COUNT).quot);

		auto chunk = FindChunk(index);
		if (!chunk)
			return nullptr;

		if (localPos != nullptr)
		{
			*localPos = IntVector2(
				worldPos.x - index.x*LevelChunk::COUNT,
				worldPos.y - index.y*LevelChunk::COUNT);
		}

		return chunk;
	}
}
