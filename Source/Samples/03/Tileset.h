#pragma once
#include <Core/Object.h>
#include <Core/Video/Texture2D.h>

namespace uut
{
	struct Tile
	{
		bool alpha;
		SharedPtr<Texture2D> texture;

		Tile() : alpha(false) {}
	};

	struct FloorTile : Tile
	{
		explicit FloorTile(Texture2D* tex) { texture = tex; }
	};

	struct WallTile : Tile
	{
		explicit WallTile(Texture2D* tex) { texture = tex; }
	};

	class Tileset : public Object
	{
	public:
		Tileset();

		void Update(float deltaTime);

		int AddFloorTile(Texture2D* texture);
		int AddWallTile(Texture2D* texture, bool alpha = false);

		const FloorTile& GetFloor(int index) const { return _floorTiles[index]; }
		const WallTile& GetWall(int index) const { return _wallTiles[index]; }

		int GetFloorCount() const { return _floorTiles.Count(); }
		int GetWallcount() const { return _wallTiles.Count(); }

	protected:
		List<FloorTile> _floorTiles;
		List<WallTile> _wallTiles;
	};
}