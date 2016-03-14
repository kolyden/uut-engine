#include "Tileset.h"

namespace uut
{
	Tileset::Tileset()
	{
	}

	void Tileset::Update(float deltaTime)
	{
	}

	int Tileset::AddFloorTile(Texture2D* texture)
	{
		if (texture == nullptr)
			return -1;

		_floorTiles.Add(FloorTile(texture));
		return _floorTiles.Count() - 1;
	}

	int Tileset::AddWallTile(Texture2D* texture, bool alpha)
	{
		if (texture == nullptr)
			return -1;

		_wallTiles.Add(WallTile(texture));
		if (alpha)
			_wallTiles[_wallTiles.Count() - 1].alpha = alpha;
		return _wallTiles.Count() - 1;
	}
}