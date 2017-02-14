#pragma once
#include <Core/Object.h>
#include <Core/Math/IntRect.h>
#include "Topology.h"
#include "Color32.h"
#include "Viewport.h"

namespace uut
{
	class Texture2D;
	class VertexBuffer;
	class IndexBuffer;
	class PipelineState;

	class CommandList : public Object
	{
		UUT_OBJECT(uut, CommandList, Object)
	public:
		virtual void Reset(const SharedPtr<PipelineState>& state) = 0;
		virtual void Close() = 0;

		virtual bool Clear(const Color32& color = Color32::White, float z = 1.0f, uint32_t stencil = 0) = 0;
		virtual void SetViewport(const Viewport& viewport) = 0;
		virtual void SetScissorRect(const IntRect& rect) = 0;

		virtual void SetTopology(Topology topology) = 0;
		virtual Topology GetTopology() const = 0;

		virtual bool SetTexture(int stage, const SharedPtr<Texture2D>& texture) = 0;
		virtual bool SetVertexBuffer(const SharedPtr<VertexBuffer>& buffer, uint16_t stride, uint32_t offset = 0) = 0;
		virtual bool SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer) = 0;

		virtual bool DrawPrimitive(uint32_t primitiveCount, uint32_t offset = 0) = 0;
		virtual bool DrawIndexedPrimitive(int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount) = 0;
	};
}