#include "DX9IndexBuffer.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9IndexBuffer)
	{}

	DX9IndexBuffer::DX9IndexBuffer()
		: _data(nullptr)
	{
	}

	DX9IndexBuffer::~DX9IndexBuffer()
	{
		_data->Release();
	}

	void* DX9IndexBuffer::Lock(uint32_t size, uint32_t offset)
	{
		void* buf;
		HRESULT ret = _data->Lock(offset, size, &buf, D3DLOCK_DISCARD);
		if (ret != D3D_OK)
			return nullptr;

		return buf;
	}

	void DX9IndexBuffer::Unlock()
	{
		_data->Unlock();
	}

	intptr_t DX9IndexBuffer::GetInternalHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}