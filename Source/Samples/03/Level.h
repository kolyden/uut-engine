#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>
#include <Core/Collections/List.h>
#include "Entity.h"

namespace uut
{
	class Entity;
	class Graphics;
	class Tileset;
	class LevelChunk;

	class Level : public Object
	{
	public:
		explicit Level(Tileset* tileset);

		Tileset* GetTileset() const { return _tileset; }
		LevelChunk* FindChunk(int x, int y) const { return FindChunk(IntVector2(x, y)); }
		LevelChunk* FindChunkAt(int x, int y, IntVector2* localPos) const { return FindChunkAt(IntVector2(x, y), localPos); }

		void PlaceEntity(Entity* entity, const IntVector2& position);
		Entity* GetEntityAt(const IntVector2& index) const;

		virtual void Update(float deltaTime);
		virtual void Draw(Graphics* graphics) const = 0;

		virtual LevelChunk* FindChunk(const IntVector2& index) const = 0;
		virtual LevelChunk* FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const = 0;

	protected:
		SharedPtr<Tileset> _tileset;
		List<SharedPtr<Entity>> _entities;
	};
}