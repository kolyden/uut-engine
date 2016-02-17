#pragma once
#include "DX9Defs.h"
#include "Core/Video/VertexDeclaration.h"

namespace uut
{
	class DX9VertexDeclaration : public VertexDeclaration
	{
	public:
		DX9VertexDeclaration();
		virtual ~DX9VertexDeclaration();

		uintptr_t GetInternalHandle() const override;

	protected:
		LPDIRECT3DVERTEXDECLARATION9 _data;

		friend class DX9Renderer;
	};
}