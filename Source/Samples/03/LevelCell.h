#pragma once
#include <cstdint>

namespace uut
{
	enum class Direction
	{
		North,
		East,
		South,
		West,
	};

	struct LevelCell
	{
		typedef uint8_t TileIndex;

		static const TileIndex EMPTY_TILE = 255;
		static const float SIZE;
		static const float HALF_SIZE;

		bool empty;
		TileIndex floor;
		TileIndex wall[4];

		LevelCell();
		void Clear();

		void SetFloor(TileIndex tile);
		void SeWall(Direction dir, TileIndex tile);

		int GetWall(Direction dir) const { return wall[static_cast<int>(dir)]; }

		bool IsEmpty() const { return empty; }

		bool IsFloorEmpty() const { return floor == EMPTY_TILE; }
		bool IsWallEmpty(Direction dir) const { return wall[static_cast<int>(dir)] == EMPTY_TILE; }
	};
}