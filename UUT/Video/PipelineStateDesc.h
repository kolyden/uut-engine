#pragma once
#include "Color32.h"
#include "VertexElement.h"
#include "Topology.h"

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

	enum class FogMode
	{
		None,
		Exp,
		Exp2,
		Linear,
	};

	enum class BlendOperation // D3DBLENDOP
	{
		Add,
		Sub,
		RevSub,
		Min,
		Max,
	};

	enum class BlendFactor // D3DBLEND
	{
		Zero,
		One,
		SrcColor,
		InvSrcColor,
		SrcAlpha,
		InvSrcAlpha,
		DestColor,
		InvDestColor,
		DestAlpha,
		InvDestAlpha,
		SrcAlphaSat,
		BothSrcAlpha,
		InvBothSrcAlpha,
		Factor,
		InvFactor,
	};

	struct ZBufferState
	{
		ZBufferMode mode = ZBufferMode::ZBuffer;
		bool writeEnable = false;
		CompareFunc func = CompareFunc::LessEqual;
	};

	struct AlphaState
	{
		bool blend = false;
		bool test = false;
		uint8_t ref = 0;
		CompareFunc func = CompareFunc::Always;
	};

	struct BlendingState
	{
		BlendOperation operation;
		BlendFactor source;
		BlendFactor dest;

		static const BlendingState Texture;
		static const BlendingState Alpha;
	};

	struct LightningState
	{
		bool enabled = false;
		Color32 ambientColor = Color32::White;
	};

	struct FogState
	{
		bool enabled = false;
		Color32 color = Color32::White;
		FogMode mode = FogMode::None;
		float density = 1;
		float start = 0;
		float end = 1;
		bool rangeEnabled = false;
	};

	struct PipelineStateDesc
	{
		PipelineStateDesc();

		// Z Buffer
		ZBufferMode zbuffer;
		bool zwriteEnable;
		CompareFunc zfunc;

		// Alpha
		bool alphaBlend;
		bool alphaTest;
		uint8_t alphaRef;
		CompareFunc alphaFunc;

		// Blending
		BlendOperation blendOp;
		BlendFactor srcBlend;
		BlendFactor destBlend;
		BlendOperation blendOpAlpha;
		BlendFactor srcBlendAlpha;
		BlendFactor destBlendAlpha;

		// Lightning
		bool lightning;
		Color32 ambientColor;

		// Fog
		bool fogEnabled;
		Color32 fogColor;
		FogMode fogMode;
		float fogDensity;
		float fogStart;
		float fogEnd;
		bool fogRangeEnabled;

		FillMode fillMode;
		ShadeMode shadeMode;
		CullMode cullMode;
		bool scissorTest;

		static const int TEXTURE_STAGE_COUNT = 8;
		static const int SAMPLER_COUNT = 4;

		// Texture
		RenderTextureStageState textureStage[TEXTURE_STAGE_COUNT];
		RenderSamplerState sampler[SAMPLER_COUNT];

		List<VertexElement> inputLayout;
	};
}