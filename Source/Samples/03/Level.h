#pragma once
#include <Core/Object.h>
#include <Core/Collections/Dictionary.h>
#include <Core/Math/IntVector2.h>
#include "Entity.h"

namespace uut
{
	class Graphics;
	class Tileset;
	class LevelChunk;

	class Level : public Object
	{
	public:
		typedef Dictionary<IntVector2, SharedPtr<LevelChunk>> ChunkMap;

		explicit Level(Tileset* tileset);

		Tileset* GetTileset() const { return _tileset; }

		void PlaceEntity(Entity* entity, const IntVector2& position);

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

		LevelChunk* FindChunk(int x, int y) const { return FindChunk(IntVector2(x, y)); }
		LevelChunk* GetChunk(int x, int y) { return GetChunk(IntVector2(x, y)); }
		LevelChunk* FindChunk(const IntVector2& index) const;
		LevelChunk* GetChunk(const IntVector2& index);

		LevelChunk* FindChunkAt(int x, int y, IntVector2* localPos) const { return FindChunkAt(IntVector2(x, y), localPos); }
		LevelChunk* GetChunkAt(int x, int y, IntVector2* localPos) { return GetChunkAt(IntVector2(x, y), localPos); }
		LevelChunk* FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const;
		LevelChunk* GetChunkAt(const IntVector2& worldPos, IntVector2* localPos);

		const ChunkMap& GetChunkMap() const { return _chunks; }

	protected:
		SharedPtr<Tileset> _tileset;
		Dictionary<IntVector2, SharedPtr<LevelChunk>> _chunks;
		List<SharedPtr<Entity>> _entities;
	};
}