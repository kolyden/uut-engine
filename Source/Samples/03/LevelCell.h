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

	enum class TileBlocked : uint8_t
	{
		Empty = 0,

		WallN = 1,
		WallW = 2,
		WallE = 4,
		WallS = 8,

		WallNW = WallN | WallW,
		WallNE = WallN | WallE,
		WallSW = WallS | WallW,
		WallSE = WallS | WallE,

		WallWE = WallW | WallE,
		WallNS = WallN | WallS,

		WallNWE = WallN | WallW | WallE,
		WallNWS = WallN | WallW | WallS,
		WallNES = WallN | WallE | WallS,
		WallWES = WallW | WallE | WallS,

		Blocked = WallN | WallW | WallE | WallS,
	};

	struct CellBlocked
	{
		uint8_t blocked : 4;
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

		void ClearFloor() { floor = EMPTY_TILE; }
		void ClearWall(Direction dir) { wall[static_cast<int>(dir)] = EMPTY_TILE; }

		int GetWall(Direction dir) const { return wall[static_cast<int>(dir)]; }

		bool IsEmpty() const { return empty; }

		bool IsFloorEmpty() const { return floor == EMPTY_TILE; }
		bool IsWallEmpty(Direction dir) const { return wall[static_cast<int>(dir)] == EMPTY_TILE; }

		bool IsBlocked(Direction dir) const;
	};
}