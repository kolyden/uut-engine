#pragma once
#include "InfoLayer.h"

namespace uut
{
	class BlockedLayer : public InfoLayer<uint8_t>
	{
		UUT_OBJECT(BlockedLayer, TilemapLayer)
	public:
		BlockedLayer();

		bool MakePath(const IntVector2& start, const IntVector2& end, List<IntVector2>& path);
	};
}