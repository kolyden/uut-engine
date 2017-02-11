#include "DX9RenderState.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9RenderState)
	{}

	DX9RenderState::DX9RenderState()
		: _data(nullptr)
	{}

	DX9RenderState::~DX9RenderState()
	{
		if (_data)
			_data->Release();
	}
}