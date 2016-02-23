#include "BufferObject.h"

namespace uut
{
	BufferObject::BufferObject()
		: _size(0)
	{
	}

	bool BufferObject::UpdateData(const void* buffer, uint32_t size, uint32_t offset /* = 0 */)
	{
		if (buffer == nullptr)
			return false;

		void* dest = Lock(size, offset);
		if (dest == nullptr)
			return false;

		memcpy(dest, buffer, size);
		Unlock();
		return true;
	}
}