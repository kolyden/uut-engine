#include "DX9CommandList.h"
#include "DX9Command.h"
#include "DX9PipelineState.h"

namespace uut
{
	static D3DPRIMITIVETYPE Convert(Topology topology)
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

	UUT_OBJECT_IMPLEMENT(DX9CommandList)
	{}

	DX9CommandList::DX9CommandList()
	{}

	DX9CommandList::~DX9CommandList()
	{}

	void DX9CommandList::Reset(const SharedPtr<PipelineState>& state)
	{
		_commands.Clear();
		_state = DynamicCast<DX9PipelineState>(state);
		_topology = Topology::TriangleList;
	}

	void DX9CommandList::Close()
	{
	}

	void DX9CommandList::SetViewport(const Viewport& viewport)
	{
		_viewport = viewport;
	}

	void DX9CommandList::SetScissorRect(const IntRect& rect)
	{
		_scissorRect = rect;
	}

	void DX9CommandList::SetTopology(Topology topology)
	{
		_topology = topology;
	}

	Topology DX9CommandList::GetTopology() const
	{
		return _topology;
	}

	bool DX9CommandList::SetTexture(int stage, const SharedPtr<Texture2D>& texture)
	{
		auto cmd = SharedPtr<TextureDX9Command>::Make();
		cmd->stage = stage;
		cmd->texture = texture;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::SetVertexBuffer(const SharedPtr<VertexBuffer>& buffer, uint16_t stride, uint32_t offset /*= 0*/)
	{
		auto cmd = SharedPtr<VBufferDX9Command>::Make();
		cmd->stride = stride;
		cmd->offset = offset;
		cmd->buffer = buffer;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer)
	{
		auto cmd = SharedPtr<IBufferDX9Command>::Make();
		cmd->buffer = buffer;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::DrawPrimitive(uint32_t primitiveCount, uint32_t offset /*= 0*/)
	{
		auto cmd = SharedPtr<DrawDX9Command>::Make();
		cmd->primitiveType = Convert(_topology);
		cmd->primitiveCount = primitiveCount;
		cmd->offset = offset;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::DrawIndexedPrimitive(int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount)
	{
		auto cmd = SharedPtr<DrawIndexedDX9Command>::Make();
		cmd->primitiveType = Convert(_topology);
		cmd->baseVertexIndex = baseVertexIndex;
		cmd->minVertexIndex = minVertexIndex;
		cmd->numVertices = numVertices;
		cmd->startIndex = startIndex;
		cmd->primitiveCount = primitiveCount;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::Clear(const Color32& color /*= Color32::White*/, float z /*= 1.0f*/, uint32_t stencil /*= 0*/)
	{
		auto cmd = SharedPtr<ClearDX9Command>::Make();
		cmd->flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		cmd->color = color.ToInt();
		cmd->z = z;
		cmd->stencil = stencil;
		_commands.Add(cmd);
		return true;
	}
}