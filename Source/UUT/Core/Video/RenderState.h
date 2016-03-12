#pragma once
#include "Color32.h"
#include "Core/Math/IntRect.h"

namespace uut
{
	enum class TextureOperation //D3DTEXTUREOP
	{
		Disable,
		SelectArg1,
		SelectArg2,
		Modulate,
		Modulate2x,
		Modulate4x,
		Add,
		AddSigned,
		AddSigned2x,
		Substract,
		AddSmooth,
		BlendDiffuseAlpha,
		BlendTextureAlpha,
		BlendFactorAlpha,
		BlendTextureAlphaPM,
		BlendCurrentAlpha,
		PreModulate,
		ModulateAlphaAddColor,
		ModulateColorAddAlpha,
		BumpEnvMap,
		BumpEnvMapLuminance,
		DotProduct3,
		MultiplyAdd,
		Lerp,
	};

	enum class TextureStageType
	{
		AlphaArg0,
		AlphaArg1,
		AlphaArg2,
		ColorArg0,
		ColorArg1,
		ColorArg2,
	};

	enum class TextureArgument // D3DTA
	{
		Constant,
		Current,
		Diffuse,
		SelectMask,
		Specular,
		Temp,
		Texture,
		TextureFactor,
	};

	struct RenderTextureStageState
	{
		TextureOperation colorOp;
		TextureArgument colorArg1;
		TextureArgument colorArg2;
		TextureOperation alphaOp;
		TextureArgument alphaArg1;
		TextureArgument alphaArg2;

		static const RenderTextureStageState Disabled;
		static const RenderTextureStageState Opaque;
		static const RenderTextureStageState Transparent;

		RenderTextureStageState();
		RenderTextureStageState(
			TextureOperation colop, TextureArgument colarg1, TextureArgument colarg2,
			TextureOperation alpop, TextureArgument alparg1, TextureArgument alparg2);
	};

	enum class TextureFilter // D3DTEXTUREFILTERTYPE
	{
		NoFilter,
		Point,
		Linear,
		Anisotropic,
		PyramidalQuad,
		GaussianQuad,
	};

	enum class TextureAddress // D3DTEXTUREADDRESS 
	{
		Wrap,
		Mirror,
		Clamp,
		Border,
		MirrorOnce,
	};

	struct RenderSamplerState
	{
		TextureAddress addressu;
		TextureAddress addressv;
		TextureAddress addressw;
		Color32 borderColor;
		TextureFilter minFilter;
		TextureFilter magFilter;
		TextureFilter mipFilter;

		RenderSamplerState();
	};

	enum class ZBufferMode // D3DZBUFFERTYPE
	{
		Disable,
		ZBuffer,
		WBuffer,
	};

	enum class FillMode // D3DFILLMODE 
	{
		Point,
		Wireframe,
		Solid,
	};

	enum class ShadeMode // D3DSHADEMODE
	{
		Flat,
		Gourand,
		Phong,
	};

	enum class CullMode // D3DCULLMODE
	{
		Disabled,
		Clockwise,
		ConterClockwise,
	};

	enum class CompareFunc // D3DCMPFUNC 
	{
		Never,
		Less,
		Equal,
		LessEqual,
		Greater,
		NotEqual,
		GreaterEqual,
		Always,
	};

	struct RenderState
	{
		enum BlendOp // D3DBLENDOP
		{
			BLENDOP_ADD,
			BLENDOP_SUB,
			BLENDOP_REVSUB,
			BLENDOP_MIN,
			BLENDOP_MAX,
		};

		enum Blend // D3DBLEND
		{
			BLEND_ZERO,
			BLEND_ONE,
			BLEND_SRCCOLOR,
			BLEND_INVSRCCOLOR,
			BLEND_SRCALPHA,
			BLEND_INVSRCALPHA,
			BLEND_DESTCOLOR,
			BLEND_INVDESTCOLOR,
			BLEND_DESTALPHA,
			BLEND_INVDESTALPHA,
			BLEND_SRCALPHASAT,
			BLEND_BOTHSRCALPHA,
			BLEND_INVBOTHSRCALPHA,
			BLEND_BLENDFACTOR,
			BLEND_INVBLENDFACTOR,
		};

		ZBufferMode zbuffer;
		FillMode fillMode;
		ShadeMode shadeMode;
		bool zwriteEnable;
		bool alphaTest;
		Blend srcBlend;
		Blend destBlend;
		CullMode cullMode;
		CompareFunc zfunc;
		CompareFunc alphaFunc;
		bool alphaBlend;
		bool fogEnabled;
		Color32 fogColor;
		//fog
		//stencil
		bool lightning;
		Color32 ambientColor;

		BlendOp blendOp;
		bool scissorTest;
		Blend srcBlendAlpha;
		Blend destBlendAlpha;
		BlendOp blendOpAlpha;

// 		IntRect scissorRect;

		static const int TEXTURE_STAGE_COUNT = 8;
		static const int SAMPLER_COUNT = 4;

		// Texture
		RenderTextureStageState textureStage[TEXTURE_STAGE_COUNT];
		RenderSamplerState sampler[SAMPLER_COUNT];

		RenderState();
	};
}