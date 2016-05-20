#pragma once
#include <Resources/Resource.h>
#include <Core/Math/IntRect.h>

namespace uut
{
	class Texture2D;

	class Tileset : public Resource
	{
		UUT_OBJECT(Tileset, Resource)
	public:
		Tileset();

		void SetTexture(Texture2D* texture);
		Texture2D* GetTexture() const;

		void SetRects(const List<IntRect>& rects);
		const List<IntRect>& GetRects() const;

	protected:
		List<IntRect> _tiles;
		SharedPtr<Texture2D> _texture;
	};
}