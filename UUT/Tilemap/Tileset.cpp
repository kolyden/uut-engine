#include "Tileset.h"
#include <Video/Texture2D.h>
#include <Core/Math/Vector2.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Tileset)
	{}

	Tileset::Tileset()
	{
	}

	void Tileset::SetTexture(Texture2D* texture)
	{
		if (_texture == texture)
			return;

		_texture = texture;
		UpdateNormalizedRects();
	}

	Texture2D* Tileset::GetTexture() const
	{
		return _texture;
	}

	void Tileset::SetItems(const List<TilesetItem>& items)
	{
		_items = items;
		UpdateNormalizedRects();
	}

	const List<TilesetItem>& Tileset::GetItems() const
	{
		return _items;
	}

	void Tileset::GenerateItems(const IntVector2& tileSize)
	{
		if (tileSize.x <= 0 || tileSize.y <= 0 ||
			!_texture)
			return;

		const auto& size = _texture->GetSize();
		const int countX = div(size.x, tileSize.x).quot;
		const int countY = div(size.y, tileSize.y).quot;

		List<TilesetItem> list;
		for (int y = 0; y < countY; y++)
		{
			for (int x = 0; x < countX; x++)
				list.Add(TilesetItem(x * tileSize.x, y * tileSize.y, tileSize.x, tileSize.y));
		}

		SetItems(list);
	}

	////////////////////////////////////////////////////////
	void Tileset::UpdateNormalizedRects()
	{
		if (!_texture)
			return;

		const Vector2 size = _texture->GetSize();
		for (auto& item : _items)
		{
			item.normalizedRect = Rect(
				1.0f * item.textureRect.x / size.x,
				1.0f * item.textureRect.y / size.y,
				1.0f * item.textureRect.width / size.x,
				1.0f * item.textureRect.height / size.y);
		}
	}
}