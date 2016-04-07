#pragma once
#include "Level.h"
#include <Core/Collections/Dictionary.h>

namespace uut
{
	class EditorLevelChunk;

	class EditorLevel : public Level
	{
	public:
		explicit EditorLevel(Tileset* tileset);

		virtual void Update(float deltaTime) override;
		virtual void Draw(Graphics* graphics) const override;

		virtual LevelChunk* FindChunk(const IntVector2& index) const override;
		virtual LevelChunk* FindChunkAt(const IntVector2& worldPos, IntVector2* localPos) const override;

		EditorLevelChunk* GetChunk(int x, int y) { return GetChunk(IntVector2(x, y)); }
		EditorLevelChunk* GetChunk(const IntVector2& index);

		EditorLevelChunk* GetChunkAt(int x, int y, IntVector2* localPos) { return GetChunkAt(IntVector2(x, y), localPos); }
		EditorLevelChunk* GetChunkAt(const IntVector2& worldPos, IntVector2* localPos);

	protected:
		Dictionary<IntVector2, SharedPtr<EditorLevelChunk>> _chunks;
 	};
}