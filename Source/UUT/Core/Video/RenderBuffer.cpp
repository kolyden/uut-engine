#include "RenderBuffer.h"

namespace uut
{
	RenderBuffer::RenderBuffer()
		: _size(0)
	{
	}

	bool RenderBuffer::UpdateData(const void* buffer, uint32_t size, uint32_t offset /* = 0 */)
	{
		if (buffer == nullptr)
			return false;

		void* dest = Lock(offset, size);
		if (dest == nullptr)
			return false;

		memcpy(dest, buffer, size);
		Unlock();
		return true;
	}
}