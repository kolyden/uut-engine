#pragma once
#include <Resources/Resource.h>
#include <Core/Math/Recti.h>
#include <Core/Math/Rect.h>

namespace uut
{
	class Texture2D;

	class Sprite : public Resource
	{
		UUT_OBJECT(uut, Sprite, Resource)
	public:
		Sprite();

		void SetTexture(const SharedPtr<Texture2D>& texture);
		const SharedPtr<Texture2D>& GetTexture() const;

		void SetRect(const Recti& rect);
		const Recti& GetRect() const;

		void SetTextureRect(const Rect& rect);
		const Rect& GetTextureRect() const;

		static SharedPtr<Sprite> Create(const SharedPtr<Texture2D>& texture, const Recti& rect);

	protected:
		SharedPtr<Texture2D> _texture;
		Recti _rect;
		Rect _textureRect;
	};
}