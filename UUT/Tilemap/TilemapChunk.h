#pragma once
#include <Core/Math/IntVector3.h>
#include <Core/Math/Vector3.h>

namespace uut
{
	class TilemapChunk
	{
	public:

	protected:
		uint16_t _id;
		Vector3 _position;
		IntVector3 _index;
		IntVector3 _size;
	};
}