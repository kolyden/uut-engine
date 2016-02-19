#include "DX9VertexBuffer.h"

namespace uut
{
	DX9VertexBuffer::DX9VertexBuffer()
		: _data(nullptr)
	{
	}

	DX9VertexBuffer::~DX9VertexBuffer()
	{
		_data->Release();
	}

	void* DX9VertexBuffer::Lock(uint32_t size, uint32_t offset)
	{
		void* buf;
		HRESULT ret = _data->Lock(offset, size, &buf, D3DLOCK_DISCARD);
		if (ret != D3D_OK)
			return nullptr;

		return buf;
	}

	void DX9VertexBuffer::Unlock()
	{
		_data->Unlock();
	}

	uint32_t DX9VertexBuffer::GetInternalHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}