#pragma once
#include <Video/CommandList.h>

namespace uut
{
	class IDX9Command;
	class DX9RenderState;

	class DX9CommandList : public CommandList
	{
		UUT_OBJECT(uut, DX9CommandList, CommandList)
	public:
		DX9CommandList();
		virtual ~DX9CommandList();

		virtual void Reset(const SharedPtr<RenderState>& state) override;
		virtual void Close() override;

		virtual bool Clear(const Color32& color, float z, uint32_t stencil) override;
		virtual void SetViewport(const Viewport& viewport) override;
		virtual void SetScissorRect(const IntRect& rect) override;

		virtual bool SetTexture(int stage, const SharedPtr<Texture2D>& texture) override;
		virtual bool SetVertexBuffer(const SharedPtr<VertexBuffer>& buffer, uint16_t stride, uint32_t offset = 0) override;
		virtual bool SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer) override;

		virtual bool DrawPrimitive(uint32_t primitiveCount, uint32_t offset = 0) override;
		virtual bool DrawIndexedPrimitive(int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount) override;

	protected:
		Viewport _viewport;
		IntRect _scissorRect;
		List<SharedPtr<IDX9Command>> _commands;
		SharedPtr<DX9RenderState> _state;

		friend class DX9Renderer;
	};
}