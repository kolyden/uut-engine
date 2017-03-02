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

		virtual SharedPtr<PipelineState> CreatePipelineState(const PipelineStateDesc& desc) override;

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
		RendererStatistics _statistics;
		Matrix4 _matView;
		Matrix4 _matWorld;
		Matrix4 _matProj;

		static bool TestReturnCode(HRESULT ret);
	};
}