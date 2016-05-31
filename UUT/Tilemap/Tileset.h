#pragma once
#include <Resources/Resource.h>
#include <Core/Math/IntRect.h>
#include <Core/Math/Rect.h>

namespace uut
{
	class Texture2D;

	struct TilesetItem
	{
		IntRect textureRect;
		Rect normalizedRect;

		TilesetItem() : textureRect(IntRect::Zero) {}
		explicit TilesetItem(const IntRect& rect) : textureRect(rect) {}
		TilesetItem(int x, int y, int w, int h) : textureRect(x, y, w, h) {}
	};

	class Tileset : public Resource
	{
		UUT_OBJECT(Tileset, Resource)
	public:
		Tileset();

		void SetTexture(Texture2D* texture);
		Texture2D* GetTexture() const;

		void SetItems(const List<TilesetItem>& items);
		const List<TilesetItem>& GetItems() const;

		void GenerateItems(const IntVector2& tileSize);

	protected:
		List<TilesetItem> _items;
		SharedPtr<Texture2D> _texture;

		void UpdateNormalizedRects();
	};
}
