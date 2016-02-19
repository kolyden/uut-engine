#pragma once
#include "Core/Video/Renderer.h"
#include "DX9Defs.h"

namespace uut
{
	class DX9Renderer : public Renderer
	{
	public:
		virtual ~DX9Renderer();

		virtual void ResetStates() override;
		virtual void SetState(RenderState state, bool enabled) override;
		virtual void SetScissorRect(const IntRect& rect) override;

		virtual bool SetTransform(RenderTransform type, const Matrix4& mat) override;

		virtual bool BeginScene() override;
		virtual void EndScene() override;

		virtual bool SetTexture(int stage, Texture2D* texture) override;
		virtual bool SetVertexBuffer(VertexBuffer* buffer, uint16_t stride, uint32_t offset) override;
		virtual bool SetIndexBuffer(IndexBuffer* buffer) override;
		virtual bool SetVertexDeclaration(VertexDeclaration* declare) override;

		virtual bool DrawPrimitive(Topology topology, uint32_t primitiveCount, uint32_t offset) override;
		virtual bool DrawIndexedPrimitive(Topology topology, int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount) override;

		virtual bool Clear(const Color& color, float z, uint32_t stencil) override;
		virtual bool Present() override;

		virtual SharedPtr<Texture2D> CreateTexture(const IntVector2& size, TextureAccess access) override;
		virtual SharedPtr<VertexBuffer> CreateVertexBuffer(uint32_t size) override;
		virtual SharedPtr<IndexBuffer> CreateIndexBuffer(uint32_t size, bool use32) override;
		virtual SharedPtr<VertexDeclaration> CreateVertexDeclaration(const VertexElement* elements, uint8_t count) override;

		static SharedPtr<DX9Renderer> Create(Window* window);

	protected:
		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3ddev;

		DX9Renderer();

		bool TestReturnCode(HRESULT ret) const;

		static D3DTRANSFORMSTATETYPE Convert(RenderTransform type);
		static D3DPRIMITIVETYPE Convert(Topology topology);
		static D3DDECLTYPE Convert(VertexElement::DeclareType type);
		static D3DDECLUSAGE Convert(VertexElement::UsageType usage);
	};
}