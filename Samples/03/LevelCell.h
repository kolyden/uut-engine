#pragma once
#include <cstdint>

namespace uut
{
	class Tileset;

	enum class Direction
	{
		North,
		East,
		South,
		West,
	};

	enum class CellType : uint8_t
	{
		Empty,
		Solid,
		Walls,
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

	typedef uint8_t TileIndex;

	struct LevelCell
	{
		LevelCell();

		void Clear();

		void SetFloor(TileIndex tile);
		void SetSolid(TileIndex tile);
		void SetWall(Direction dir, TileIndex tile);

		void ClearFloor() { floor = EmptyTile; }
		void ClearWall(Direction dir) { wall[static_cast<int>(dir)] = EmptyTile; }

		int GetFloor() const { return floor; }
		int GetWall(Direction dir) const { return wall[static_cast<int>(dir)]; }

		bool IsEmpty() const { return type == CellType::Empty; }
		bool IsSolid() const { return type == CellType::Solid; }
		bool IsWalls() const { return type == CellType::Walls; }

		bool IsFloorEmpty() const { return floor == EmptyTile; }

		bool IsWallEmpty(Direction dir) const;

		bool IsBlocked() const;
		bool IsBlocked(Direction dir, Tileset* tileset) const;

		static const TileIndex EmptyTile = 255;
		static const float Size;
		static const float HalfSize;
		static const float WallSize;
		static const LevelCell Empty;

		CellType type;
		TileIndex floor;
		TileIndex wall[4];
	};
}