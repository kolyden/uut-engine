#pragma once
#include <Resources/Resource.h>
#include <Core/Math/Rect.h>

namespace uut
{
	class Texture2D;

	class TextureAtlas : public Resource
	{
		UUT_OBJECT(TextureAtlas, Resource)
	public:

		void SetTexture(const SharedPtr<Texture2D>& texture);
		const SharedPtr<Texture2D>& GetTexture() const;

		void SetRects(const List<Rect>& rects);
		const List<Rect>& GetRects() const;

		static SharedPtr<TextureAtlas> Create(const SharedPtr<Texture2D>& texture, const List<IntRect>& rects);
		static SharedPtr<TextureAtlas> Create(const SharedPtr<Texture2D>& texture, uint width, uint height, uint count = 0);

	protected:
		SharedPtr<Texture2D> _texture;
		List<Rect> _rects;
	};
}