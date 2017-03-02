#include "DX9CommandList.h"
#include "DX9Command.h"
#include "DX9PipelineState.h"
#include "DX9Texture2D.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"

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

		SetPipelineState(state);
	}

	void DX9CommandList::Close()
	{
	}

	void DX9CommandList::SetViewport(const Viewport& viewport)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_VIEWPORT;
		cmd.viewport = D3DVIEWPORT9
		{
			viewport.x, viewport.y,
			viewport.width, viewport.height,
			viewport.minZ, viewport.maxZ
		};
		_commands.Add(cmd);
	}

	void DX9CommandList::SetScissorRect(const IntRect& rect)
	{
		const RECT r{ rect.GetLeft(),rect.GetTop(),rect.GetRight(),rect.GetBottom() };

		DX9Command cmd;
		cmd.type = DX9Command::TYPE_SCISSOR;
		cmd.rect = r;
		_commands.Add(cmd);
	}

	void DX9CommandList::SetPipelineState(const SharedPtr<PipelineState>& state)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_PIPELINE;
		cmd.object = state;
		_commands.Add(cmd);
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
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_TEXTURE;
		cmd.stage = stage;
		cmd.object = texture;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::SetVertexBuffer(const SharedPtr<VertexBuffer>& buffer, uint16_t stride, uint32_t offset /*= 0*/)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_VBUFFER;
		cmd.stride = stride;
		cmd.offset = offset;
		cmd.object = buffer;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::SetIndexBuffer(const SharedPtr<IndexBuffer>& buffer)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_IBUFFER;
		cmd.object = buffer;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::DrawPrimitive(uint32_t primitiveCount, uint32_t offset /*= 0*/)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_DRAW;
		cmd.primitiveType = Convert(_topology);
		cmd.primitiveCount = primitiveCount;
		cmd.offset = offset;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::DrawIndexedPrimitive(int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_DRAWIND;
		cmd.primitiveType = Convert(_topology);
		cmd.baseVertexIndex = baseVertexIndex;
		cmd.minVertexIndex = minVertexIndex;
		cmd.numVertices = numVertices;
		cmd.startIndex = startIndex;
		cmd.primitiveCount = primitiveCount;
		_commands.Add(cmd);
		return true;
	}

	bool DX9CommandList::Clear(const Color32& color /*= Color32::White*/, float z /*= 1.0f*/, uint32_t stencil /*= 0*/)
	{
		DX9Command cmd;
		cmd.type = DX9Command::TYPE_CLEAR;
		cmd.flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		cmd.color = color.ToInt();
		cmd.z = z;
		cmd.stencil = stencil;
		_commands.Add(cmd);
		return true;
	}
}