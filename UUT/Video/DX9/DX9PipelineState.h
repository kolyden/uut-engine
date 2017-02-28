#pragma once
#include <Video/PipelineState.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9PipelineState : public PipelineState
	{
		UUT_OBJECT(uut, DX9PipelineState, PipelineState)
	public:
		DX9PipelineState();
		virtual ~DX9PipelineState();

		LPDIRECT3DVERTEXDECLARATION9 _vd;

		friend class DX9Renderer;
	};
}