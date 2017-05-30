#include "Sprite.h"
#include "Texture2D.h"
#include <Core/Math/Vector2.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Sprite)
	{}

	Sprite::Sprite()
	{
	}

	void Sprite::SetTexture(const SharedPtr<Texture2D>& texture)
	{
		_texture = texture;
	}

	const SharedPtr<Texture2D>& Sprite::GetTexture() const
	{
		return _texture;
	}

	void Sprite::SetRect(const IntRect& rect)
	{
		_rect = rect;
	}

	const IntRect& Sprite::GetRect() const
	{
		return _rect;
	}

	void Sprite::SetTextureRect(const Rect& rect)
	{
		_textureRect = rect;
	}

	const Rect& Sprite::GetTextureRect() const
	{
		return _textureRect;
	}

	SharedPtr<Sprite> Sprite::Create(const SharedPtr<Texture2D>& texture, const IntRect& rect)
	{
		if (texture == nullptr)
			return nullptr;

		const Vector2i& size = texture->GetSize();
		const float invW = 1.0f / size.x;
		const float invH = 1.0f / size.y;
		const Rect textureRect(
			invW * rect.x, invH * rect.y,
			invW * rect.width, invH * rect.height);

		auto spr = MakeShared<Sprite>();
		spr->SetTexture(texture);
		spr->SetRect(rect);
		spr->SetTextureRect(textureRect);
		return spr;
	}
}