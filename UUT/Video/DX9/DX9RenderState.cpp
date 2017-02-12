#include "DX9RenderState.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9RenderState)
	{}

	DX9RenderState::DX9RenderState()
		: _vd(nullptr)
	{}

	DX9RenderState::~DX9RenderState()
	{
		if (_vd)
			_vd->Release();
	}
}