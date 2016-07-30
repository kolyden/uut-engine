#pragma once
#include <Resources/Resource.h>
#include "Color.h"
#include "RenderState.h"

namespace uut
{
	class Texture2D;

	class Material : public Resource
	{
		UUT_OBJECT(Material, Resource)
	public:
		Material();

		void SetTexture(const SharedPtr<Texture2D>& texture);
		const SharedPtr<Texture2D>& GetTexture() const;

		void SetColor(const Color& color);
		const Color& GetColor() const;

		void SetAlphaBlend(bool value);
		bool IsAlphaBlend() const;

		void SetAlphaTest(bool value);
		bool IsAlphaTest() const;

		void SetTextureStage(const RenderTextureStageState& stage);
		const RenderTextureStageState& GetTextureStage() const;

	protected:
		SharedPtr<Texture2D> _texture;
		Color _color;
		bool _alphaBlend;
		bool _alphaTest;
		RenderTextureStageState _textureStage;
	};
}