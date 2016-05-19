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

		virtual void Update(float deltaTime) = 0;
		virtual void Draw(Graphics* graphics) const = 0;
		virtual LevelChunk* GetNeighbor(Direction dir) const = 0;

		const LevelCell& GetCell(const IntVector2& pos) const { return GetCell(pos.x, pos.y); }
		const LevelCell& GetCell(int x, int y) const;

		const Vector3& GetPosition() const { return _position; }
		IntVector2 GetGlobalPos(int x, int y) const;
		IntVector2 GetGlobalPos(const IntVector2& localPos) const;

		static unsigned GetIndex(int x, int y) { return y * COUNT + x; }

		static const int COUNT = 16;
		static const int TOTAL_COUNT = COUNT*COUNT;

	protected:
		WeakPtr<Level> _level;
		IntVector2 _index;
		LevelCell _cells[TOTAL_COUNT];
		Vector3 _position;

// 		static void DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color);
// 		static void DrawWall(Graphics* graphics, const Vector3& center, Direction dir, Texture2D* texture, const Color32& color);

		friend class Level;
	};
}