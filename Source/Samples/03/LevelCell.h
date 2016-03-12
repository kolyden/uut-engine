#pragma once
#include <cstdint>

namespace uut
{
	enum class CellType
	{
		Empty,
		Solid,
		Normal,
	};

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

		CellType type;
		TileIndex floor;
		TileIndex wall[4];

		void Clear();

		void SetSolid(TileIndex roof, TileIndex side);

		void SetNormalFloor(TileIndex tile) { type = CellType::Normal; floor = tile; }
		void SetNormalWall(Direction dir, TileIndex tile) { type = CellType::Normal; wall[static_cast<int>(dir)] = tile; }

		int GetWall(Direction dir) const { return wall[static_cast<int>(dir)]; }

		bool IsEmpty() const { return type == CellType::Empty; }
		bool IsSolid() const { return type == CellType::Solid; }
		bool IsNormal() const { return type == CellType::Normal; }

		bool IsFloorEmpty() const { return floor == EMPTY_TILE; }
		bool IsWallEmpty(Direction dir) const { return wall[static_cast<int>(dir)] == EMPTY_TILE; }
	};
}