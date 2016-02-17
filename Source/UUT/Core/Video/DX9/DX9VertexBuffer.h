#pragma once
#include "DX9Defs.h"
#include "Core/Video/VertexBuffer.h"

namespace uut
{
	class DX9VertexBuffer : public VertexBuffer
	{
	public:
		DX9VertexBuffer();
		virtual ~DX9VertexBuffer();

		virtual void* Lock(uint32_t offset, uint32_t size) override;
		virtual void Unlock() override;

		uint32_t GetInternalHandle() const override;

	protected:
		LPDIRECT3DVERTEXBUFFER9 _data;

		friend class DX9Renderer;
	};
}