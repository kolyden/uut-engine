#include "Tileset.h"
#include <Video/Texture2D.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Tileset)
	{}

	Tileset::Tileset()
	{
	}

	void Tileset::SetTexture(Texture2D* texture)
	{
		_texture = texture;
	}

	Texture2D* Tileset::GetTexture() const
	{
		return _texture;
	}

	void Tileset::SetRects(const List<IntRect>& rects)
	{
		_tiles = rects;
	}

	const List<IntRect>& Tileset::GetRects() const
	{
		return _tiles;
	}
}