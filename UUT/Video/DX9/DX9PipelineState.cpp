#include "DX9PipelineState.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DX9PipelineState)
	{}

	DX9PipelineState::DX9PipelineState()
		: _vd(nullptr)
	{}

	DX9PipelineState::~DX9PipelineState()
	{
		if (_vd)
			_vd->Release();
	}
}