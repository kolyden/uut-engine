#pragma once
#include <Core/Object.h>
#include "LevelCell.h"
#include <Core/Math/IntVector2.h>
#include <Core/Math/Vector3.h>

namespace uut
{
	class Color32;
	class Texture2D;
	class Level;
	class Graphics;

	class LevelChunk : public Object
	{
	public:
		LevelChunk(Level* level, const IntVector2& index);
		virtual ~LevelChunk();

		Level* GetLevel() const { return _level; }

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

		void Clear();

		LevelCell& GetCell(const IntVector2& pos) { return GetCell(pos.x, pos.y); }
		const LevelCell& GetCell(const IntVector2& pos) const { return GetCell(pos.x, pos.y); }

		LevelCell& GetCell(int x, int y);
		const LevelCell& GetCell(int x, int y) const;

		const uint8_t* GetBitmask() const { return _bitmask; }

		const Vector3& GetPosition() const { return _position; }
		IntVector2 GetGlobalPos(const IntVector2& localPos) const;

		static unsigned GetIndex(int x, int y) { return y * COUNT + x; }

		static const int COUNT = 16;
		static const int TOTAL_COUNT = COUNT*COUNT;

	protected:
		WeakPtr<Level> _level;
		WeakPtr<LevelChunk> _neighbor[4];
		IntVector2 _index;
		LevelCell _cells[TOTAL_COUNT];
		uint8_t _bitmask[TOTAL_COUNT];
		Vector3 _position;

		void UpdateBitmask();
		void ForeachCell(List<LevelCell>::Iterate func);
		void ForeachCell(List<LevelCell>::ConstIterate func) const;

		void SetNeighbor(Direction dir, LevelChunk* chunk);

		static void DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color);
// 		static void DrawWall(Graphics* graphics, const Vector3& center, Direction dir, Texture2D* texture, const Color32& color);

		friend class Level;
	};
}