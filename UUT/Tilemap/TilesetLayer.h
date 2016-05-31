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
		const uint8_t EMPTY_TILE = 255;
		using IterateFunc = std::function<void(int x, int y, uint8_t& tile)>;

		TilesetLayer();

		void SetTransparent(bool transparent);
		bool GetTransparent() const;

		void SetTileset(Tileset* tileset);
		Tileset* GetTileset() const;

		void SetTile(int x, int y, uint8_t tile);
		uint8_t GetTile(int x, int y) const;

		void Fill(uint8_t tile);
		void Fill(const IntRect& rect, uint8_t tile);
		void Clear();
		void ForEach(IterateFunc func);

		virtual void SetSize(const IntVector2& size) override;
		virtual void Update(float deltaTime) override;
		virtual void DrawLayer(Graphics* graphics) const override;

	protected:
		SharedPtr<Tileset> _tileset;
		List<uint8_t> _tiles;
		IntVector2 _size;
		bool _transparent;

		int Pos2Index(int x, int y) const;
		IntVector2 Index2Pos(int index) const;
	};
}