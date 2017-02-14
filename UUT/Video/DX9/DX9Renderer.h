#pragma once
#include <Video/Renderer.h>
#include <Video/PipelineState.h>
#include <Video/Viewport.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9PipelineState;

	class DX9Renderer : public Renderer
	{
		UUT_MODULE(uut, DX9Renderer, Renderer)
	public:
		DX9Renderer();
		virtual ~DX9Renderer();

		virtual SharedPtr<PipelineState> CreateRenderState(const PipelineStateDesc& desc) override;

		virtual const RendererStatistics& GetStatistics() const override;

		virtual bool SetTransform(RenderTransform type, const Matrix4& mat) override;
		virtual const Matrix4& GetTransform(RenderTransform type) const override;

		virtual bool BeginScene() override;
		virtual void EndScene() override;

		virtual void Execute(const SharedPtr<CommandList>& commandList) override;

		virtual bool Present() override;

		virtual SharedPtr<Texture2D> CreateTexture(const IntVector2& size, TextureAccess access) override;
		virtual SharedPtr<VertexBuffer> CreateVertexBuffer(uint32_t size) override;
		virtual SharedPtr<IndexBuffer> CreateIndexBuffer(uint32_t size, bool use32) override;
		virtual SharedPtr<CommandList> CreateCommandList() override;

		static SharedPtr<DX9Renderer> Create(const SharedPtr<Window>& window);

	protected:
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3ddev;
		PipelineStateDesc _state;
		RendererStatistics _statistics;
		Matrix4 _matView;
		Matrix4 _matWorld;
		Matrix4 _matProj;

		static bool TestReturnCode(HRESULT ret);

		void SetPipeline(const PipelineStateDesc& state, bool force = false);

		static D3DTRANSFORMSTATETYPE Convert(RenderTransform type);
		static D3DPRIMITIVETYPE Convert(Topology topology);
		static D3DDECLTYPE Convert(VertexElement::DeclareType type);
		static D3DDECLUSAGE Convert(VertexElement::UsageType usage);

		static D3DZBUFFERTYPE Convert(ZBufferMode type);
		static D3DFILLMODE Convert(FillMode mode);
		static D3DSHADEMODE Convert(ShadeMode mode);
		static D3DCULL Convert(CullMode mode);
		static D3DCMPFUNC Convert(CompareFunc func);
		static D3DFOGMODE Convert(FogMode mode);

		static D3DTEXTUREOP Convert(TextureOperation op);
		static DWORD Convert(TextureArgument arg);
		static D3DTEXTUREFILTERTYPE Convert(TextureFilter filter);
		static D3DTEXTUREADDRESS Convert(TextureAddress address);

		static D3DBLENDOP Convert(BlendOperation op);
		static D3DBLEND Convert(BlendFactor blend);
	};
}