#pragma once
#include <Video/RenderState.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9RenderState : public RenderState
	{
		UUT_OBJECT(uut, DX9RenderState, RenderState)
	public:
		DX9RenderState();
		virtual ~DX9RenderState();

		LPDIRECT3DVERTEXDECLARATION9 _data;

		friend class DX9Renderer;
	};
}