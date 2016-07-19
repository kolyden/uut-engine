#include "TilemapChunk.h"

namespace uut
{
	TilemapChunk::TilemapChunk(const SharedPtr<Tilemap>& tilemap, const IntVector3& index)
		: _tilemap(tilemap)
		, _index(index)
	{
	}

	const IntVector3& TilemapChunk::GetIndex() const
	{
		return _index;
	}

	const IntVector3& TilemapChunk::GetSize() const
	{
		return _size;
	}
}
