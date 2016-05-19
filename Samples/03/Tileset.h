#pragma once
#include <Core/Object.h>
#include <Core/Video/Texture2D.h>
#include "Tile.h"

namespace uut
{
	enum class TileType : uint8_t
	{
		Floor,
		Wall,
		Door,
		Window,
	};

	struct TileInfo
	{
		TileType type;
		bool blocked;
	};

	class Tileset : public Object
	{
	public:
		Tileset();

		void Update(float deltaTime);

		int AddFloorTile(Texture2D* texture);
		int AddWallTile(Texture2D* texture, bool alpha = false);

		FloorTile* GetFloor(int index) const;
		WallTile* GetWall(int index) const;

		int GetFloorCount() const { return _floorTiles.Count(); }
		int GetWallcount() const { return _wallTiles.Count(); }

	protected:
		List<SharedPtr<FloorTile>> _floorTiles;
		List<SharedPtr<WallTile>> _wallTiles;
	};
}