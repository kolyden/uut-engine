#include "EditorLevel.h"
#include <Core/Math/Math.h>
#include <Core/Video/Graphics.h>
#include "EditorLevelChunk.h"
#include "Tileset.h"

namespace uut
{
	EditorLevel::EditorLevel(Tileset* tileset)
		: Level(tileset)
	{
	}

	void EditorLevel::Update(float deltaTime)
	{
		_tileset->Update(deltaTime);
		for (auto& it : _chunks)
			it.second->Update(deltaTime);

		Level::Update(deltaTime);
	}

	void EditorLevel::Draw(Graphics* graphics, FreeCamera* camera) const
	{
		if (graphics == nullptr)
			return;

		for (auto& it : _chunks)
			it.second->Draw(graphics);

		for (uint i = 0; i < _entities.Count(); i++)
			_entities[i]->Draw(graphics, camera);
		graphics->Flush();
	}

	LevelChunk* EditorLevel::FindChunk(const IntVector2& index) const
	{
		auto it = _chunks.Find(index);
		return it != _chunks.End() ? it->second.Get() : nullptr;
	}

	LevelChunk* EditorLevel::FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const
	{
		const IntVector2 index(
			Math::FloorToInt(static_cast<float>(worldPos.x) / LevelChunk::COUNT),
			Math::FloorToInt(static_cast<float>(worldPos.y) / LevelChunk::COUNT));

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

	EditorLevelChunk* EditorLevel::GetChunk(const IntVector2& index)
	{
		auto chunk = FindChunk(index);
		if (chunk)
			return static_cast<EditorLevelChunk*>(chunk);

		auto tmp = new EditorLevelChunk(this, index);
		_chunks[index] = tmp;

		static const IntVector2 order[4] = {
			IntVector2(0, 1), IntVector2(1,0),
			IntVector2(0,-1), IntVector2(-1,0)
		};

		for (int i = 0; i < 4; i++)
		{
			tmp->SetNeighbor(Direction::North,
				static_cast<EditorLevelChunk*>(FindChunk(index + order[i])));
		}

		return tmp;
	}

	EditorLevelChunk* EditorLevel::GetChunkAt(const IntVector2& worldPos, IntVector2* localPos)
	{
		const IntVector2 index(
			Math::FloorToInt(static_cast<float>(worldPos.x) / LevelChunk::COUNT),
			Math::FloorToInt(static_cast<float>(worldPos.y) / LevelChunk::COUNT));

		auto chunk = GetChunk(index);
		if (localPos != nullptr)
		{
			*localPos = IntVector2(
				worldPos.x - index.x*LevelChunk::COUNT,
				worldPos.y - index.y*LevelChunk::COUNT);
		}

		return chunk;
	}
}