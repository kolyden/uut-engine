#pragma once
#include "BufferObject.h"

namespace uut
{
	class VertexBuffer : public BufferObject
	{
		UUT_OBJECT(VertexBuffer, BufferObject)
	public:
		VertexBuffer();
		virtual ~VertexBuffer();
	};
}