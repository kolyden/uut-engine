#pragma once
#include "LevelChunk.h"

namespace uut
{
	class EditorLevelChunk : public LevelChunk
	{
	public:
		EditorLevelChunk(Level* level, const IntVector2& index);

		virtual void Update(float deltaTime) override;
		virtual void Draw(Graphics* graphics) const override;
		virtual LevelChunk* GetNeighbor(Direction dir) const override;

		void Clear();

		const uint8_t* GetBitmask() const { return _wallmask; }

		LevelCell& GetCell(const IntVector2& pos) { return GetCell(pos.x, pos.y); }
		LevelCell& GetCell(int x, int y);

	protected:
		uint8_t _wallmask[TOTAL_COUNT];
		WeakPtr<EditorLevelChunk> _neighbor[4];

		static void DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color);

		void UpdateBitmask();
		void SetNeighbor(Direction dir, EditorLevelChunk* chunk);

		friend class EditorLevel;
	};
}