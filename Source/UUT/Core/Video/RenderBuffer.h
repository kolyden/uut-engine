#pragma once
#include "Core/Object.h"

namespace uut
{
	class RenderBuffer : public Object
	{
	public:
		RenderBuffer();
		virtual ~RenderBuffer() {}

		uint32_t GetSize() const { return _size; }

		virtual void* Lock(uint32_t size, uint32_t offset = 0) = 0;
		virtual void Unlock() = 0;

		bool UpdateData(const void* buffer, uint32_t size, uint32_t offset = 0);

		virtual uint32_t GetInternalHandle() const = 0;

	protected:
		uint32_t _size;
	};
}