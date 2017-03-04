#pragma once
#include <Video/Renderer.h>
#include <Video/CommandList.h>
#include <Video/PipelineStateDesc.h>

#define NOMINMAX
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

namespace uut
{
	namespace dx9
	{
		extern D3DTRANSFORMSTATETYPE Convert(RenderTransform type);
		extern D3DPRIMITIVETYPE Convert(Topology topology);
		extern D3DDECLTYPE Convert(VertexElement::DeclareType type);
		extern D3DDECLUSAGE Convert(VertexElement::UsageType usage);

		extern D3DZBUFFERTYPE Convert(ZBufferMode type);
		extern D3DFILLMODE Convert(FillMode mode);
		extern D3DSHADEMODE Convert(ShadeMode mode);
		extern D3DCULL Convert(CullMode mode);
		extern D3DCMPFUNC Convert(CompareFunc func);
		extern D3DFOGMODE Convert(FogMode mode);

		extern D3DTEXTUREOP Convert(TextureOperation op);
		extern DWORD Convert(TextureArgument arg);
		extern D3DTEXTUREFILTERTYPE Convert(TextureFilter filter);
		extern D3DTEXTUREADDRESS Convert(TextureAddress address);

		extern D3DBLENDOP Convert(BlendOperation op);
		extern D3DBLEND Convert(BlendFactor blend);
	}
}