#pragma once
#include <Video/VertexBuffer.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9VertexBuffer : public VertexBuffer
	{
		UUT_OBJECT(uut, DX9VertexBuffer, VertexBuffer)
	public:
		DX9VertexBuffer();
		virtual ~DX9VertexBuffer();

		virtual void* Lock(uint32_t offset, uint32_t size) override;
		virtual void Unlock() override;

		intptr_t GetInternalHandle() const override;

	protected:
		LPDIRECT3DVERTEXBUFFER9 _data;

		friend class DX9Renderer;
	};
}