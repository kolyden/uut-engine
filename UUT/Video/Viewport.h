#pragma once
#include <Core/ValueType.h>

namespace uut
{
	class Vector2i;

	class Viewport : public ValueType
	{
		UUT_VALUETYPE(uut, Viewport, ValueType)
	public:
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
		float minZ;
		float maxZ;

		constexpr Viewport() : x(0), y(0), width(0), height(0), minZ(0), maxZ(1) {}

		Viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		Viewport(uint32_t x, uint32_t y, const Vector2i& size);
		Viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float minZ, float maxZ);
	};
}