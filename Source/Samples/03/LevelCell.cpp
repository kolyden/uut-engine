#include "LevelCell.h"

namespace uut
{
	const float LevelCell::SIZE = 3.0f;
	const float LevelCell::HALF_SIZE = SIZE / 2;

	LevelCell::LevelCell()
		: empty(true)
		, floor(0)
	{
		wall[0] = EMPTY_TILE;
		wall[1] = EMPTY_TILE;
		wall[2] = EMPTY_TILE;
		wall[3] = EMPTY_TILE;
	}

	void LevelCell::Clear()
	{
		empty = true;
		floor = EMPTY_TILE;
		wall[0] = EMPTY_TILE;
		wall[1] = EMPTY_TILE;
		wall[2] = EMPTY_TILE;
		wall[3] = EMPTY_TILE;
	}

	void LevelCell::SetFloor(TileIndex tile)
	{
		empty = false;
		floor = tile;
	}

	void LevelCell::SeWall(Direction dir, TileIndex tile)
	{
		empty = false;
		wall[static_cast<int>(dir)] = tile;
	}

	bool LevelCell::IsBlocked(Direction dir) const
	{
		return !IsWallEmpty(dir);
	}
}