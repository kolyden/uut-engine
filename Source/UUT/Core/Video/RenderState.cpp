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
		, fillMode(FillMode::Solid)
		, shadeMode(ShadeMode::Gourand)
		, zwriteEnable(false)
		, alphaTest(false)
		, srcBlend(BLEND_SRCALPHA)
		, destBlend(BLEND_INVSRCALPHA)
		, cullMode(CullMode::ConterClockwise)
		, zfunc(CompareFunc::LessEqual)
		, alphaFunc(CompareFunc::Always)

		, alphaBlend(false)
		, fogEnabled(false)
		, fogColor(Color32::Clear)
		, lightning(false)
		, blendOp(BLENDOP_ADD)
		, scissorTest(false)
		
		, srcBlendAlpha(BLEND_ONE)
		, destBlendAlpha(BLEND_ZERO)
		, blendOpAlpha(BLENDOP_ADD)
	{
		textureStage[0] = RenderTextureStageState::Opaque;
	}
}