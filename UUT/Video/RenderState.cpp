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

	const BlendingState BlendingState::Texture{ BlendOperation::Add, BlendFactor::SrcAlpha, BlendFactor::InvSrcAlpha };
	const BlendingState BlendingState::Alpha{ BlendOperation::Add, BlendFactor::One, BlendFactor::One };

	RenderState::RenderState()
		: zbuffer(ZBufferMode::ZBuffer)
		, zwriteEnable(false)
		, zfunc(CompareFunc::LessEqual)

		, alphaBlend(false)
		, alphaTest(false)
		, alphaRef(0)
		, alphaFunc(CompareFunc::Always)

		, blendOp(BlendOperation::Add)
		, srcBlend(BlendFactor::SrcAlpha)
		, destBlend(BlendFactor::InvSrcAlpha)
		, blendOpAlpha(BlendOperation::Add)
		, srcBlendAlpha(BlendFactor::One)
		, destBlendAlpha(BlendFactor::One)

		, lightning(false)
		, ambientColor(Color32::White)

		, fogEnabled(false)
		, fogColor(Color32::White)
		, fogMode(FogMode::None)
		, fogDensity(1)
		, fogStart(0)
		, fogEnd(1)
		, fogRangeEnabled(false)

		, fillMode(FillMode::Solid)
		, shadeMode(ShadeMode::Gourand)
		, cullMode(CullMode::ConterClockwise)
		, scissorTest(false)
	{
		textureStage[0] = RenderTextureStageState::Opaque;
	}
}