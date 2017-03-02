#include "DX9Defs.h"

namespace uut
{
	namespace dx9
	{
		D3DTRANSFORMSTATETYPE Convert(RenderTransform type)
		{
			switch (type)
			{
			case RenderTransform::RT_VIEW: return D3DTS_VIEW;
			case RenderTransform::RT_PROJECTION: return D3DTS_PROJECTION;
			case RenderTransform::RT_WORLD: return D3DTS_WORLD;
			}
			return D3DTS_FORCE_DWORD;

		}

		D3DPRIMITIVETYPE Convert(Topology topology)
		{
			switch (topology)
			{
			case Topology::PointList: return D3DPT_POINTLIST;
			case Topology::LineList: return D3DPT_LINELIST;
			case Topology::LineStrip: return D3DPT_LINESTRIP;
			case Topology::TriangleList: return D3DPT_TRIANGLELIST;
			case Topology::TriangleStrip: return D3DPT_TRIANGLESTRIP;
			case Topology::TriangleFan: return D3DPT_TRIANGLEFAN;
			}

			return D3DPT_POINTLIST;
		}

		D3DDECLTYPE Convert(VertexElement::DeclareType type)
		{
			switch (type)
			{
			case VertexElement::DT_FLOAT1: return D3DDECLTYPE_FLOAT1;
			case VertexElement::DT_FLOAT2: return D3DDECLTYPE_FLOAT2;
			case VertexElement::DT_FLOAT3: return D3DDECLTYPE_FLOAT3;
			case VertexElement::DT_FLOAT4: return D3DDECLTYPE_FLOAT4;
			case VertexElement::DT_DWORD: return D3DDECLTYPE_D3DCOLOR;
			case VertexElement::DT_UBYTE4: return D3DDECLTYPE_UBYTE4;
			}

			return D3DDECLTYPE_UNUSED;
		}

		D3DDECLUSAGE Convert(VertexElement::UsageType usage)
		{
			switch (usage)
			{
			case VertexElement::UT_POSITION: return D3DDECLUSAGE_POSITION;
			case VertexElement::UT_NORMAL: return D3DDECLUSAGE_NORMAL;
			case VertexElement::UT_TEXCOORD: return D3DDECLUSAGE_TEXCOORD;
			case VertexElement::UT_COLOR: return D3DDECLUSAGE_COLOR;
			}

			return D3DDECLUSAGE_POSITION;
		}

		D3DZBUFFERTYPE Convert(ZBufferMode type)
		{
			switch (type)
			{
			case ZBufferMode::Disable: return D3DZB_FALSE;
			case ZBufferMode::ZBuffer: return D3DZB_TRUE;
			case ZBufferMode::WBuffer: return D3DZB_USEW;
			}

			return D3DZB_FALSE;
		}

		D3DFILLMODE Convert(FillMode mode)
		{
			switch (mode)
			{
			case FillMode::Point: return D3DFILL_POINT;
			case FillMode::Wireframe: return D3DFILL_WIREFRAME;
			case FillMode::Solid: return D3DFILL_SOLID;
			}

			return D3DFILL_SOLID;
		}

		D3DSHADEMODE Convert(ShadeMode mode)
		{
			switch (mode)
			{
			case ShadeMode::Flat: return D3DSHADE_FLAT;
			case ShadeMode::Gourand: return D3DSHADE_GOURAUD;
			case ShadeMode::Phong: return D3DSHADE_PHONG;
			}

			return D3DSHADE_GOURAUD;
		}

		D3DCULL Convert(CullMode mode)
		{
			switch (mode)
			{
			case CullMode::Clockwise: return D3DCULL_CW;
			case CullMode::ConterClockwise: return D3DCULL_CCW;
			}

			return D3DCULL_NONE;
		}

		D3DCMPFUNC Convert(CompareFunc func)
		{
			switch (func)
			{
			case CompareFunc::Never: return D3DCMP_NEVER;
			case CompareFunc::Less: return D3DCMP_LESS;
			case CompareFunc::Equal: return D3DCMP_EQUAL;
			case CompareFunc::LessEqual: return D3DCMP_LESSEQUAL;
			case CompareFunc::Greater: return D3DCMP_GREATER;
			case CompareFunc::NotEqual: return D3DCMP_NOTEQUAL;
			case CompareFunc::GreaterEqual: return D3DCMP_GREATEREQUAL;
			case CompareFunc::Always: return D3DCMP_ALWAYS;
			}

			return D3DCMP_LESSEQUAL;
		}

		D3DFOGMODE Convert(FogMode mode)
		{
			switch (mode)
			{
			case FogMode::None: return D3DFOG_NONE;
			case FogMode::Exp: return D3DFOG_EXP;
			case FogMode::Exp2: return D3DFOG_EXP2;
			case FogMode::Linear: return D3DFOG_LINEAR;
			}

			return D3DFOG_NONE;
		}

		D3DTEXTUREOP Convert(TextureOperation op)
		{
			switch (op)
			{
			case TextureOperation::Disable: return D3DTOP_DISABLE;
			case TextureOperation::SelectArg1: return D3DTOP_SELECTARG1;
			case TextureOperation::SelectArg2: return D3DTOP_SELECTARG2;
			case TextureOperation::Modulate: return D3DTOP_MODULATE;
			case TextureOperation::Modulate2x: return D3DTOP_MODULATE2X;
			case TextureOperation::Modulate4x: return D3DTOP_MODULATE4X;
			case TextureOperation::Add: return D3DTOP_ADD;
			case TextureOperation::AddSigned: return D3DTOP_ADDSIGNED;
			case TextureOperation::AddSigned2x: return D3DTOP_ADDSIGNED2X;
			case TextureOperation::Substract: return D3DTOP_SUBTRACT;
			case TextureOperation::AddSmooth: return D3DTOP_ADDSMOOTH;
			case TextureOperation::BlendDiffuseAlpha: return D3DTOP_BLENDDIFFUSEALPHA;
			case TextureOperation::BlendTextureAlpha: return D3DTOP_BLENDTEXTUREALPHA;
			case TextureOperation::BlendFactorAlpha: return D3DTOP_BLENDFACTORALPHA;
			case TextureOperation::BlendTextureAlphaPM: return D3DTOP_BLENDTEXTUREALPHAPM;
			case TextureOperation::BlendCurrentAlpha: return D3DTOP_BLENDCURRENTALPHA;
			case TextureOperation::PreModulate: return D3DTOP_PREMODULATE;
			case TextureOperation::ModulateAlphaAddColor: return D3DTOP_MODULATEALPHA_ADDCOLOR;
			case TextureOperation::ModulateColorAddAlpha: return D3DTOP_MODULATECOLOR_ADDALPHA;
			case TextureOperation::BumpEnvMap: return D3DTOP_BUMPENVMAP;
			case TextureOperation::BumpEnvMapLuminance: return D3DTOP_BUMPENVMAPLUMINANCE;
			case TextureOperation::DotProduct3: return D3DTOP_DOTPRODUCT3;
			case TextureOperation::MultiplyAdd: return D3DTOP_MULTIPLYADD;
			case TextureOperation::Lerp: return D3DTOP_LERP;
			}

			return D3DTOP_ADD;
		}

		DWORD Convert(TextureArgument arg)
		{
			switch (arg)
			{
			case TextureArgument::Constant: return D3DTA_CONSTANT;
			case TextureArgument::Current: return D3DTA_CURRENT;
			case TextureArgument::Diffuse: return D3DTA_DIFFUSE;
			case TextureArgument::SelectMask: return D3DTA_SELECTMASK;
			case TextureArgument::Specular: return D3DTA_SPECULAR;
			case TextureArgument::Temp: return D3DTA_TEMP;
			case TextureArgument::Texture: return D3DTA_TEXTURE;
			case TextureArgument::TextureFactor: return D3DTA_TFACTOR;
			}

			return D3DTA_TEXTURE;
		}

		D3DTEXTUREFILTERTYPE Convert(TextureFilter filter)
		{
			switch (filter)
			{
			case TextureFilter::NoFilter: return D3DTEXF_NONE;
			case TextureFilter::Point: return D3DTEXF_POINT;
			case TextureFilter::Linear: return D3DTEXF_LINEAR;
			case TextureFilter::Anisotropic: return D3DTEXF_ANISOTROPIC;
			case TextureFilter::PyramidalQuad: return D3DTEXF_PYRAMIDALQUAD;
			case TextureFilter::GaussianQuad: return D3DTEXF_GAUSSIANQUAD;
			}

			return D3DTEXF_LINEAR;
		}

		D3DTEXTUREADDRESS Convert(TextureAddress address)
		{
			switch (address)
			{
			case TextureAddress::Wrap: return D3DTADDRESS_WRAP;
			case TextureAddress::Mirror: return D3DTADDRESS_MIRROR;
			case TextureAddress::Clamp: return D3DTADDRESS_CLAMP;
			case TextureAddress::Border: return D3DTADDRESS_BORDER;
			case TextureAddress::MirrorOnce: return D3DTADDRESS_MIRRORONCE;
			}

			return D3DTADDRESS_WRAP;
		}

		D3DBLENDOP Convert(BlendOperation op)
		{
			switch (op)
			{
			case BlendOperation::Add: return D3DBLENDOP_ADD;
			case BlendOperation::Sub: return D3DBLENDOP_SUBTRACT;
			case BlendOperation::RevSub: return D3DBLENDOP_REVSUBTRACT;
			case BlendOperation::Min: return D3DBLENDOP_MIN;
			case BlendOperation::Max: return D3DBLENDOP_MAX;
			}

			return D3DBLENDOP_ADD;
		}

		D3DBLEND Convert(BlendFactor blend)
		{
			switch (blend)
			{
			case BlendFactor::Zero: return D3DBLEND_ZERO;
			case BlendFactor::One: return D3DBLEND_ONE;
			case BlendFactor::SrcColor: return D3DBLEND_SRCCOLOR;
			case BlendFactor::InvSrcColor: return D3DBLEND_INVSRCCOLOR;
			case BlendFactor::SrcAlpha: return D3DBLEND_SRCALPHA;
			case BlendFactor::InvSrcAlpha: return D3DBLEND_INVSRCALPHA;
			case BlendFactor::DestColor: return D3DBLEND_DESTCOLOR;
			case BlendFactor::InvDestColor: return D3DBLEND_INVDESTCOLOR;
			case BlendFactor::DestAlpha: return D3DBLEND_DESTALPHA;
			case BlendFactor::InvDestAlpha: return D3DBLEND_INVDESTALPHA;
			case BlendFactor::SrcAlphaSat: return D3DBLEND_SRCALPHASAT;
			case BlendFactor::BothSrcAlpha: return D3DBLEND_BOTHSRCALPHA;
			case BlendFactor::InvBothSrcAlpha: return D3DBLEND_BOTHINVSRCALPHA;
			case BlendFactor::Factor: return D3DBLEND_BLENDFACTOR;
			case BlendFactor::InvFactor: return D3DBLEND_INVBLENDFACTOR;
			}

			return D3DBLEND_ZERO;
		}
	}
}