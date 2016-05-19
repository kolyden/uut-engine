#pragma once
#include <cstdint>

namespace uut
{
	class Viewport
	{
	public:
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
		float minZ;
		float maxZ;
	};
}