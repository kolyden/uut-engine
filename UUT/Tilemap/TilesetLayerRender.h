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

		void SetTilesetLayer(SharedPtr<TilesetLayer> layer);
		SharedPtr<TilesetLayer> GetTilesetLayer() const;

		virtual void Draw(Graphics* graphics) const override;

	protected:
		WeakPtr<TilesetLayer> _tilesetLayer;
	};
}