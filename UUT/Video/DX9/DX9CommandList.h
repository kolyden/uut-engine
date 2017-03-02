#pragma once
#include <Video/CommandList.h>
#include "DX9Command.h"

namespace uut
{
	class DX9PipelineState;

	class DX9CommandList : public CommandList
	{
		UUT_OBJECT(uut, DX9CommandList, CommandList)
	public:
		DX9CommandList();
		virtual ~DX9CommandList();

		virtual void Reset(const SharedPtr<PipelineState>& state) override;
		virtual void Close() override;

		virtual bool Clear(const Color32& color, float z, uint32_t stencil) override;
		virtual void SetViewport(const Viewport& viewport) override;
		virtual void SetScissorRect(const IntRect& rect) override;
		virtual void SetPipelineState(const SharedPtr<PipelineState>& state) override;

		virtual void SetTopology(Topology topology) override;
		virtual Topology GetTopology() const override;

		virtual bool SetTexture(int stage, const SharedPtr<Texture2D>& texture) override;
		virtual bool SetVertexBuffer(const SharedPtr<VertexBuffer>& buffer, uint16_t stride, uint32_t offset = 0) override;
		virtual bool SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer) override;

		virtual bool DrawPrimitive(uint32_t primitiveCount, uint32_t offset = 0) override;
		virtual bool DrawIndexedPrimitive(int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount) override;

	protected:
		List<DX9Command> _commands;
		SharedPtr<DX9PipelineState> _state;
		Topology _topology;

		friend class DX9Renderer;
	};
}