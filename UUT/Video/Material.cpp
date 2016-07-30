#include "Material.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Material)
	{}

	Material::Material()
		: _alphaBlend(false)
		, _alphaTest(false)
		, _textureStage(RenderTextureStageState::Opaque)
	{
	}

	void Material::SetTexture(const SharedPtr<Texture2D>& texture)
	{
		_texture = texture;
	}

	const SharedPtr<Texture2D>& Material::GetTexture() const
	{
		return _texture;
	}

	void Material::SetColor(const Color& color)
	{
		_color = color;
	}

	void Material::SetAlphaBlend(bool value)
	{
		_alphaBlend = value;
	}

	bool Material::IsAlphaBlend() const
	{
		return _alphaBlend;
	}

	void Material::SetAlphaTest(bool value)
	{
		_alphaTest = value;
	}

	bool Material::IsAlphaTest() const
	{
		return _alphaTest;
	}

	void Material::SetTextureStage(const RenderTextureStageState& stage)
	{
		_textureStage = stage;
	}

	const RenderTextureStageState& Material::GetTextureStage() const
	{
		return _textureStage;
	}

	const Color& Material::GetColor() const
	{
		return _color;
	}
}