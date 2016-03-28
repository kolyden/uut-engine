#include "Tileset.h"
#include "Tile.h"

namespace uut
{
	Tileset::Tileset()
	{
	}

	void Tileset::Update(float deltaTime)
	{
		for (auto& it : _floorTiles)
			it->Update(deltaTime);

		for (auto& it : _wallTiles)
			it->Update(deltaTime);
	}

	int Tileset::AddFloorTile(Texture2D* texture)
	{
		if (texture == nullptr)
			return -1;

		_floorTiles.Add(SharedPtr<FloorTile>(new SimpleFloorTile(texture)));
		return _floorTiles.Count() - 1;
	}

	int Tileset::AddWallTile(Texture2D* texture, bool alpha)
	{
		if (texture == nullptr)
			return -1;

		_wallTiles.Add(SharedPtr<WallTile>(new SimpleWallTile(texture, alpha)));
		return _wallTiles.Count() - 1;
	}

	FloorTile* Tileset::GetFloor(int index) const
	{ return _floorTiles[index]; }

	WallTile* Tileset::GetWall(int index) const
	{ return _wallTiles[index]; }
}
