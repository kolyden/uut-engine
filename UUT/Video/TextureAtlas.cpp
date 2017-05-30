#include "TextureAtlas.h"
#include "Texture2D.h"
#include <Core/Math/Recti.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TextureAtlas)
	{}

	void TextureAtlas::SetTexture(const SharedPtr<Texture2D>& texture)
	{
		if (_texture == texture)
			return;

		_texture = texture;
		if (!_texture)
		{
			_rects.Clear();
			_pixelRects.Clear();
		}
	}

	const SharedPtr<Texture2D>& TextureAtlas::GetTexture() const
	{
		return _texture;
	}

	void TextureAtlas::SetPixelRects(const List<Recti>& rects)
	{
		if (!_texture)
			return;

		if (rects.IsEmpty())
		{
			_pixelRects.Clear();
			_rects.Clear();
			return;
		}

		auto& size = _texture->GetSize();
		const float invW = 1.0f / (size.x - 1);
		const float invH = 1.0f / (size.y - 1);

		_rects.SetSize(rects.Count());
		for (size_t i = 0; i < rects.Count(); i++)
		{
			auto& r = rects[i];
			_rects[i] = Rect(invW*r.x, invH*r.y, invW*r.width, invH*r.height);
		}

		_pixelRects = rects;
	}

	const List<Recti>& TextureAtlas::GetPixelRects() const
	{
		return _pixelRects;
	}

	void TextureAtlas::SetRects(const List<Rect>& rects)
	{
		_rects = rects;
	}

	const List<Rect>& TextureAtlas::GetRects() const
	{
		return _rects;
	}

	SharedPtr<TextureAtlas> TextureAtlas::Create(const SharedPtr<Texture2D>& texture, const List<Recti>& rects)
	{
		if (texture == nullptr || rects.IsEmpty())
			return nullptr;

		auto atlas = MakeShared<TextureAtlas>();
		atlas->SetTexture(texture);
		atlas->SetPixelRects(rects);

		return atlas;
	}

	SharedPtr<TextureAtlas> TextureAtlas::Create(const SharedPtr<Texture2D>& texture, int width, int height, uint count)
	{
		if (texture == nullptr || width <= 0 || height <= 0)
			return nullptr;

		auto& size = texture->GetSize();
		if (width > size.x || height > size.y)
			return nullptr;

		const int countX = size.x / width;
		const int countY = size.y / height;

		auto atlas = MakeShared<TextureAtlas>();
		atlas->SetTexture(texture);

		if (count == 0)
			count = countX*countY;

		List<Recti> list;

		int i = 0;
		for (int y = 0; y < countY; y++)
		{
			for (int x = 0; x < countX; x++)
			{
				list.Add(Recti(x * width, y * width, width, height));

				if (i == count)
					break;
			}

			if (i == count)
				break;
		}
		atlas->SetPixelRects(list);
		return atlas;
	}
}