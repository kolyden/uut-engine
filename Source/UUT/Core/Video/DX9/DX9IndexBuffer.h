#pragma once
#include "DX9Defs.h"
#include <Core/Video/IndexBuffer.h>

namespace uut
{
	class DX9IndexBuffer : public IndexBuffer
	{
		UUT_OBJECT(DX9IndexBuffer, IndexBuffer)
	public:
		DX9IndexBuffer();
		virtual ~DX9IndexBuffer();

		virtual void* Lock(uint32_t size, uint32_t offset) override;
		virtual void Unlock() override;

		uint32_t GetInternalHandle() const override;

	protected:
		LPDIRECT3DINDEXBUFFER9 _data;

		friend class DX9Renderer;
	};
}