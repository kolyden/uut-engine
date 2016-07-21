#include "TextureAtlas.h"
#include "Texture2D.h"
#include <Core/Math/IntRect.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TextureAtlas)
	{}

	void TextureAtlas::SetTexture(const SharedPtr<Texture2D>& texture)
	{
		_texture = texture;
	}

	const SharedPtr<Texture2D>& TextureAtlas::GetTexture() const
	{
		return _texture;
	}

	void TextureAtlas::SetRects(const List<Rect>& rects)
	{
		_rects = rects;
	}

	const List<Rect>& TextureAtlas::GetRects() const
	{
		return _rects;
	}

	SharedPtr<TextureAtlas> TextureAtlas::Create(const SharedPtr<Texture2D>& texture, const List<IntRect>& rects)
	{
		if (texture == nullptr || rects.IsEmpty())
			return nullptr;

		auto atlas = MakeShared<TextureAtlas>();
		atlas->SetTexture(texture);
		auto& size = texture->GetSize();
		const float invW = 1.0f / (size.x - 1);
		const float invH = 1.0f / (size.y - 1);

		List<Rect> list;
		list.SetSize(rects.Count());
		for (size_t i = 0; i < rects.Count(); i++)
		{
			auto& r = rects[i];
			list[i] = Rect(invW*r.x, invH*r.y, invW*r.width, invH*r.height);
		}
		atlas->SetRects(list);
		return atlas;
	}

	SharedPtr<TextureAtlas> TextureAtlas::Create(const SharedPtr<Texture2D>& texture, uint width, uint height, uint count)
	{
		if (texture == nullptr || width == 0 || height == 0)
			return nullptr;

		auto& size = texture->GetSize();
		if (width > size.x || height > size.y)
			return nullptr;

		const int countX = size.x / width;
		const int countY = size.y / height;

		auto atlas = MakeShared<TextureAtlas>();
		atlas->SetTexture(texture);
		const float invW = 1.0f / size.x;
		const float invH = 1.0f / size.y;

		if (count == 0)
			count = countX*countY;

		List<Rect> list;

		int i = 0;
		for (int y = 0; y < countY; y++)
		{
			for (int x = 0; x < countX; x++)
			{
				const int offsetX = x * width;
				const int offsetY = y * width;
				list.Add(Rect(
					invW*offsetX, invH*offsetY,
					invW*width, invH*height));

				if (i == count)
					break;
			}

			if (i == count)
				break;
		}
		atlas->SetRects(list);
		return atlas;
	}
}