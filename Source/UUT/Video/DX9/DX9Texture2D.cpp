#include "DX9Texture2D.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9Texture2D)
	{}

	DX9Texture2D::DX9Texture2D()
		: _data(nullptr)
	{
	}

	DX9Texture2D::~DX9Texture2D()
	{
		if (_data)
			_data->Release();
	}

	void* DX9Texture2D::Lock(int* pitch)
	{
		if (!_data)
			return nullptr;

		D3DLOCKED_RECT rect;
		HRESULT ret = _data->LockRect(0, &rect, nullptr, 0);
		if (ret != D3D_OK)
			return nullptr;

		if (pitch != nullptr)
			*pitch = rect.Pitch;

		return rect.pBits;
	}

	void DX9Texture2D::Unlock()
	{
		if (_data)
			_data->UnlockRect(0);
	}

	intptr_t DX9Texture2D::GetNativeHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}