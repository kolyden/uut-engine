#pragma once
#include "TilemapLayer.h"

namespace uut
{
	class IntRect;
	class Tileset;

	class TilesetLayer : public TilemapLayer
	{
		UUT_OBJECT(TilesetLayer, TilemapLayer)
	public:
		TilesetLayer();

		void SetTileset(Tileset* tileset);
		Tileset* GetTileset() const;

		void SetTile(int x, int y, uint8_t tile);
		uint8_t GetTile(int x, int y) const;

		void Fill(const IntRect& rect, uint8_t tile);
		void Clear();

		virtual void SetSize(const IntVector2& size) override;
		virtual void Update(float deltaTime) override;
		virtual void DrawLayer(Graphics* graphics) const override;

	protected:
		SharedPtr<Tileset> _tileset;
		List<uint8_t> _tiles;
		IntVector2 _size;

		int Pos2Index(int x, int y) const;
	};
}