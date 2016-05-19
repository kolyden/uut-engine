#include "LevelCell.h"
#include "Tileset.h"

namespace uut
{
	const float LevelCell::Size = 3.0f;
	const float LevelCell::HalfSize = Size / 2;
	const float LevelCell::WallSize = 0.2f;
	const LevelCell LevelCell::Empty;

	LevelCell::LevelCell()
		: type(CellType::Empty)
		, floor(0)
	{
		wall[0] = EmptyTile;
		wall[1] = EmptyTile;
		wall[2] = EmptyTile;
		wall[3] = EmptyTile;
	}

	void LevelCell::Clear()
	{
		type = CellType::Empty;
		floor = EmptyTile;
		wall[0] = EmptyTile;
		wall[1] = EmptyTile;
		wall[2] = EmptyTile;
		wall[3] = EmptyTile;
	}

	void LevelCell::SetFloor(TileIndex tile)
	{
		type = CellType::Walls;
		floor = tile;
	}

	void LevelCell::SetSolid(TileIndex tile)
	{
		type = CellType::Solid;
		floor = tile;
	}

	void LevelCell::SetWall(Direction dir, TileIndex tile)
	{
		type = CellType::Walls;
		wall[static_cast<int>(dir)] = tile;
	}

	bool LevelCell::IsWallEmpty(Direction dir) const
	{
		return wall[static_cast<int>(dir)] == EmptyTile;
	}

	bool LevelCell::IsBlocked() const
	{
		return type != CellType::Walls;
	}

	bool LevelCell::IsBlocked(Direction dir, Tileset* tileset) const
	{
		if (type != CellType::Walls)
			return true;

		if (tileset == nullptr)
			return !IsWallEmpty(dir);

		auto index = wall[static_cast<int>(dir)];
		if (index == EmptyTile)
			return false;

		auto tile = tileset->GetWall(index);
		return tile->IsBlocked();
	}
}