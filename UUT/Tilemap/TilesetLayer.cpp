#include "TilesetLayer.h"
#include "Tileset.h"
#include "Tilemap.h"
#include <Video/Graphics.h>
#include <Core/Math/Rect.h>
#include <Core/Math/Vector2.h>
#include <Video/Texture2D.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilesetLayer)
	{}

	TilesetLayer::TilesetLayer()
		: _size(0)
	{
	}

	void TilesetLayer::SetTileset(Tileset* tileset)
	{
		_tileset = tileset;
	}

	Tileset* TilesetLayer::GetTileset() const
	{
		return _tileset;
	}

	void TilesetLayer::SetTile(int x, int y, uint8_t tile)
	{
		_tiles[Pos2Index(x, y)] = tile;
	}

	uint8_t TilesetLayer::GetTile(int x, int y) const
	{
		return _tiles[Pos2Index(x, y)];
	}

	void TilesetLayer::Fill(const IntRect& rect, uint8_t tile)
	{
	}

	void TilesetLayer::Clear()
	{
// 		Fill(IntRect(0, 0, _size), 0);
		for (uint i = 0; i < _tiles.Count(); i++)
			_tiles[i] = 0;
	}

	void TilesetLayer::SetSize(const IntVector2& size)
	{
		_size = size;
		_tiles.SetSize(_size.Area());
	}

	void TilesetLayer::Update(float deltaTime)
	{
	}

	void TilesetLayer::DrawLayer(Graphics* graphics) const
	{
		if (_tileset == nullptr)
			return;

		graphics->SetMaterial(Graphics::MT_OPAQUE);
		auto tex = _tileset->GetTexture();
		const Vector2 texSize = tex->GetSize();
		auto& rects = _tileset->GetRects();

		for (int y = 0; y < _size.y; y++)
		{
			for (int x = 0; x < _size.x; x++)
			{
				int index = Pos2Index(x, y);
				auto texRect = Rect(rects[index]);
				texRect.x /= texSize.x;
				texRect.y /= texSize.y;
				texRect.width /= texSize.x;
				texRect.height /= texSize.y;

				graphics->DrawQuad(Rect(), 0, tex, texRect);
			}
		}
	}

	////////////////////////////////////////////////////////////////////
	int TilesetLayer::Pos2Index(int x, int y) const
	{
		return y*_size.x + x;
	}
}
