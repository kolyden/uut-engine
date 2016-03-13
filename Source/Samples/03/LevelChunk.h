#pragma once
#include <Core/Object.h>
#include "LevelCell.h"
#include <Core/Math/IntVector2.h>
#include <Core/Math/Vector3.h>

namespace uut
{
	struct WallTile;
	struct FloorTile;
	class Level;
	class Graphics;

	class LevelChunk : public Object
	{
	public:
		LevelChunk(Level* level, const IntVector2& index);

		Level* GetLevel() const { return _level; }

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

		void Clear();

		LevelCell& GetCell(const IntVector2& pos) { return GetCell(pos.x, pos.y); }
		const LevelCell& GetCell(const IntVector2& pos) const { return GetCell(pos.x, pos.y); }

		LevelCell& GetCell(int x, int y) { return _cells[GetIndex(x, y)]; }
		const LevelCell& GetCell(int x, int y) const { return _cells[GetIndex(x, y)]; }

		static unsigned GetIndex(int x, int y) { return y * COUNT + x; }

		static const int COUNT = 16;
		static const int TOTAL_COUNT = COUNT*COUNT;

	protected:
		WeakPtr<Level> _level;
		IntVector2 _index;
		LevelCell _cells[TOTAL_COUNT];
		Vector3 _position;

		void ForeachCell(List<LevelCell>::Iterate func);
		void ForeachCell(List<LevelCell>::ConstIterate func) const;

		static void DrawFloor(Graphics* graphics, const FloorTile& tile, const Vector3& center);
		static void DrawWall(Graphics* graphics, const WallTile& tile, const Vector3& center, Direction dir);
	};
}