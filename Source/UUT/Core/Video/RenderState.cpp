#include "RenderState.h"

namespace uut
{
	RenderTextureStageState::RenderTextureStageState()
		: colorOp(TextureOperation::Disable)
		, colorArg1(TextureArgument::Texture)
		, colorArg2(TextureArgument::Current)
		, alphaOp(TextureOperation::Disable)
		, alphaArg1(TextureArgument::Texture)
		, alphaArg2(TextureArgument::Current)
	{		
	}

	RenderSamplerState::RenderSamplerState()
		: addressu(TextureAddress::Wrap)
		, addressv(TextureAddress::Wrap)
		, addressw(TextureAddress::Wrap)
		, borderColor(Color32::EMPTY)
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
		, fogColor(Color32::EMPTY)
		, lightning(false)
		, blendOp(BLENDOP_ADD)
		, scissorTest(false)
		
		, srcBlendAlpha(BLEND_ONE)
		, destBlendAlpha(BLEND_ZERO)
		, blendOpAlpha(BLENDOP_ADD)
	{
		textureStage[0].colorOp = TextureOperation::Modulate;
		textureStage[0].alphaOp = TextureOperation::SelectArg1;
	}
}