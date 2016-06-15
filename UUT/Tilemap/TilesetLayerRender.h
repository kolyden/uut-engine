#pragma once
#include "TilemapRender.h"

namespace uut
{
	class TilesetLayer;

	class TilesetLayerRender : public TilemapRender
	{
		UUT_OBJECT(TilesetLayerRender, TilemapRender)
	public:
		TilesetLayerRender();

		void SetTilesetLayer(TilesetLayer* layer);
		TilesetLayer* GetTilesetLayer() const;

		virtual void Draw(Graphics* graphics) const override;

	protected:
		WeakPtr<TilesetLayer> _tilesetLayer;
	};
}