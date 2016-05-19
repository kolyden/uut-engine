#pragma once
#include <Video/VertexDeclaration.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9VertexDeclaration : public VertexDeclaration
	{
		UUT_OBJECT(DX9VertexDeclaration, VertexDeclaration)
	public:
		DX9VertexDeclaration();
		virtual ~DX9VertexDeclaration();

		uintptr_t GetInternalHandle() const override;

	protected:
		LPDIRECT3DVERTEXDECLARATION9 _data;

		friend class DX9Renderer;
	};
}