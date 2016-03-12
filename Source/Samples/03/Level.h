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
		Level(Tileset* tileset);

		Tileset* GetTileset() const { return _tileset; }

		void PlaceEntity(Entity* entity, const IntVector2& position);

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

		LevelChunk* FindChunk(const IntVector2& index) const;
		LevelChunk* GetChunk(const IntVector2& index);

		LevelChunk* FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const;

	protected:
		SharedPtr<Tileset> _tileset;
		Dictionary<IntVector2, SharedPtr<LevelChunk>> _chunks;
		List<SharedPtr<Entity>> _entities;
	};
}