#include "TilesetLayer.h"
#include "Tileset.h"
#include "Tilemap.h"
#include <Video/Graphics.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilesetLayer)
	{}

	TilesetLayer::TilesetLayer()
		: _size(0)
		, _transparent(false)
	{
	}

	void TilesetLayer::SetTransparent(bool transparent)
	{
		_transparent = transparent;
	}

	bool TilesetLayer::GetTransparent() const
	{
		return _transparent;
	}

	void TilesetLayer::SetTileset(const SharedPtr<Tileset>& tileset)
	{
		_tileset = tileset;
	}

	const SharedPtr<Tileset>& TilesetLayer::GetTileset() const
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

	void TilesetLayer::Fill(uint8_t tile)
	{
		for (uint i = 0; i < _tiles.Count(); i++)
			_tiles[i] = tile;
	}

	void TilesetLayer::Fill(const IntRect& rect, uint8_t tile)
	{
	}

	void TilesetLayer::Clear()
	{
// 		Fill(IntRect(0, 0, _size), 0);
		for (uint i = 0; i < _tiles.Count(); i++)
			_tiles[i] = EMPTY_TILE;
	}

	void TilesetLayer::ForEach(IterateFunc func)
	{
		for (uint i = 0; i < _tiles.Count(); i++)
		{
			const auto pos = Index2Pos(i);
			func(pos.x, pos.y, _tiles[i]);
		}
	}

	////////////////////////////////////////////////////////////////////
	void TilesetLayer::OnSetSize(const IntVector2& size)
	{
		_size = size;
		_tiles.SetSize(_size.Area());
		Clear();
	}

	void TilesetLayer::OnRender() const
	{
		if (!_tileset)
			return;

		auto tilemap = _tilemap.Lock();
		if (!tilemap)
			return;

		ModuleInstance<Graphics> graphics;
		const auto& cellSize = tilemap->GetCellSize();
		graphics->SetMaterial(_transparent ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
		auto tex = _tileset->GetTexture();
		auto& items = _tileset->GetItems();
		for (int y = 0; y < _size.y; y++)
		{
			for (int x = 0; x < _size.x; x++)
			{
				int index = Pos2Index(x, y);
				auto tile = _tiles[index];
				if (tile == EMPTY_TILE)
					continue;
				auto& item = items[tile];
				graphics->DrawQuad(
					Rect(cellSize.x*x, cellSize.y*(tilemap->GetSize().y - y - 1), cellSize.x, cellSize.y),
					20, tex, item.normalizedRect);
			}
		}
	}

	int TilesetLayer::Pos2Index(int x, int y) const
	{
		return y*_size.x + x;
	}

	IntVector2 TilesetLayer::Index2Pos(int index) const
	{
		return IntVector2(index % _size.x, div(index, _size.x).quot);
	}
}