#include "LevelCell.h"

namespace uut
{
	const float LevelCell::SIZE = 5.0f;
	const float LevelCell::HALF_SIZE = SIZE / 2;

	void LevelCell::Clear()
	{
		type = CellType::Empty;
		floor = EMPTY_TILE;
		wall[0] = EMPTY_TILE;
		wall[1] = EMPTY_TILE;
		wall[2] = EMPTY_TILE;
		wall[3] = EMPTY_TILE;
	}

	void LevelCell::SetSolid(TileIndex roof, TileIndex side)
	{
		type = CellType::Solid;
		floor = roof;
		wall[0] = side;
		wall[1] = side;
		wall[2] = side;
		wall[3] = side;
	}
}