#include "TilesetLayerRender.h"
#include <Video/Graphics.h>
#include "TilesetLayer.h"
#include "Tilemap.h"
#include "Tileset.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilesetLayerRender)
	{}

	TilesetLayerRender::TilesetLayerRender()
	{}

	void TilesetLayerRender::SetTilesetLayer(TilesetLayer* layer)
	{
		_tilesetLayer = layer;
	}

	TilesetLayer* TilesetLayerRender::GetTilesetLayer() const
	{
		return _tilesetLayer;
	}

	void TilesetLayerRender::Draw(Graphics* graphics) const
	{
		if (_tilesetLayer == nullptr)
			return;

		auto tilemap = _tilesetLayer->GetTilemap();
		auto tileset = _tilesetLayer->GetTileset();
		if (tilemap == nullptr)
			return;

		auto& size = tilemap->GetSize();
		const auto& cellSize = tilemap->GetCellSize();

		graphics->SetMaterial(
			_tilesetLayer->GetTransparent() ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
		auto tex = tileset->GetTexture();
		auto& items = tileset->GetItems();

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				auto tile = _tilesetLayer->GetTile(x, y);
				if (tile == TilesetLayer::EMPTY_TILE)
					continue;

				auto& item = items[tile];
				graphics->DrawQuad(
					Rect(cellSize.x*x, cellSize.y*(_tilemap->GetSize().y - y - 1), cellSize.x, cellSize.y),
					20, tex, item.normalizedRect);
			}
		}
	}
}