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

	void TilesetLayerRender::SetTilesetLayer(SharedPtr<TilesetLayer> layer)
	{
		_tilesetLayer = layer;
	}

	SharedPtr<TilesetLayer> TilesetLayerRender::GetTilesetLayer() const
	{
		return _tilesetLayer.Lock();
	}

	void TilesetLayerRender::Draw(Graphics* graphics) const
	{
		if (auto layer = _tilesetLayer.Lock())
		{
			auto tilemap = layer->GetTilemap();
			auto tileset = layer->GetTileset();
			if (tilemap == nullptr)
				return;

			auto& size = tilemap->GetSize();
			const auto& cellSize = tilemap->GetCellSize();

			graphics->SetMaterial(
				layer->GetTransparent() ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
			auto tex = tileset->GetTexture();
			auto& items = tileset->GetItems();

			for (int y = 0; y < size.y; y++)
			{
				for (int x = 0; x < size.x; x++)
				{
					auto tile = layer->GetTile(x, y);
					if (tile == TilesetLayer::EMPTY_TILE)
						continue;

					auto& item = items[tile];
					graphics->DrawQuad(
						Rect(cellSize.x*x, cellSize.y*(tilemap->GetSize().y - y - 1), cellSize.x, cellSize.y),
						20, tex, item.normalizedRect);
				}
			}
		}
	}
}