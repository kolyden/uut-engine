#include "Viewport.h"
#include <Core/Math/IntVector2.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Viewport)
	{}

	Viewport::Viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height)
		: x(_x), y(_y), width(_width), height(_height), minZ(0), maxZ(1)
	{
	}

	Viewport::Viewport(uint32_t _x, uint32_t _y, const IntVector2& size)
		: x(_x), y(_y), width(size.x), height(size.y), minZ(0), maxZ(1)
	{
	}

	Viewport::Viewport(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, float _minZ, float _maxZ)
		: x(_x), y(_y), width(_width), height(_height), minZ(_minZ), maxZ(_maxZ)
	{
	}
}