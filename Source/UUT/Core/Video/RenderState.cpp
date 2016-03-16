#include "RenderState.h"

namespace uut
{

	const RenderTextureStageState RenderTextureStageState::Disabled;

	const RenderTextureStageState RenderTextureStageState::Opaque(
		TextureOperation::Modulate, TextureArgument::Texture, TextureArgument::Current,
		TextureOperation::SelectArg1, TextureArgument::Texture, TextureArgument::Current);

	const RenderTextureStageState RenderTextureStageState::Transparent(
		TextureOperation::Modulate, TextureArgument::Texture, TextureArgument::Diffuse,
		TextureOperation::Modulate, TextureArgument::Texture, TextureArgument::Diffuse);

	RenderTextureStageState::RenderTextureStageState()
		: colorOp(TextureOperation::Disable)
		, colorArg1(TextureArgument::Texture)
		, colorArg2(TextureArgument::Current)
		, alphaOp(TextureOperation::Disable)
		, alphaArg1(TextureArgument::Texture)
		, alphaArg2(TextureArgument::Current)
	{		
	}

	RenderTextureStageState::RenderTextureStageState(
		TextureOperation colop, TextureArgument colarg1, TextureArgument colarg2,
		TextureOperation alpop, TextureArgument alparg1, TextureArgument alparg2)
		: colorOp(colop)
		, colorArg1(colarg1)
		, colorArg2(colarg2)
		, alphaOp(alpop)
		, alphaArg1(alparg1)
		, alphaArg2(alparg2)
	{
	}

	RenderSamplerState::RenderSamplerState()
		: addressu(TextureAddress::Wrap)
		, addressv(TextureAddress::Wrap)
		, addressw(TextureAddress::Wrap)
		, borderColor(Color32::Clear)
		, minFilter(TextureFilter::Point)
		, magFilter(TextureFilter::Point)
		, mipFilter(TextureFilter::NoFilter)
	{
	}

	RenderState::RenderState()
		: zbuffer(ZBufferMode::ZBuffer)
		, zwriteEnable(false)
		, zfunc(CompareFunc::LessEqual)

		, alphaBlend(false)
		, alphaTest(false)
		, alphaRef(0)
		, alphaFunc(CompareFunc::Always)

		, blendOp(BLENDOP_ADD)
		, srcBlend(BLEND_SRCALPHA)
		, destBlend(BLEND_INVSRCALPHA)
		, blendOpAlpha(BLENDOP_ADD)
		, srcBlendAlpha(BLEND_ONE)
		, destBlendAlpha(BLEND_ZERO)

		, lightning(false)
		, fillMode(FillMode::Solid)
		, shadeMode(ShadeMode::Gourand)
		, cullMode(CullMode::ConterClockwise)
		, scissorTest(false)
	{
		textureStage[0] = RenderTextureStageState::Opaque;
	}
}