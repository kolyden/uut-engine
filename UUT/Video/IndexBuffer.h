#pragma once
#include <Video/BufferObject.h>

namespace uut
{
	class IndexBuffer : public BufferObject
	{
		UUT_OBJECT(IndexBuffer, BufferObject)
	public:
		IndexBuffer();
		virtual ~IndexBuffer();
	};
}