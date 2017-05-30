#pragma once
#include <Resources/Resource.h>
#include <Core/Math/Rect.h>

namespace uut
{
	class Texture2D;

	class TextureAtlas : public Resource
	{
		UUT_OBJECT(uut, TextureAtlas, Resource)
	public:

		void SetTexture(const SharedPtr<Texture2D>& texture);
		const SharedPtr<Texture2D>& GetTexture() const;

		void SetPixelRects(const List<Recti>& rects);
		const List<Recti>& GetPixelRects() const;

		void SetRects(const List<Rect>& rects);
		const List<Rect>& GetRects() const;

		static SharedPtr<TextureAtlas> Create(const SharedPtr<Texture2D>& texture, const List<Recti>& rects);
		static SharedPtr<TextureAtlas> Create(const SharedPtr<Texture2D>& texture, int width, int height, uint count = 0);

	protected:
		SharedPtr<Texture2D> _texture;
		List<Recti> _pixelRects;
		List<Rect> _rects;
	};
}