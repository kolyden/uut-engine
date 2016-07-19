#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector3.h>
#include <Core/Math/Vector3.h>

namespace uut
{
	class Tilemap;

	class TilemapChunk : public Object
	{
		UUT_OBJECT(TilemapChunk, Object)
	public:
		TilemapChunk(const SharedPtr<Tilemap>& tilemap, const IntVector3& index);

		const IntVector3& GetIndex() const;
		const IntVector3& GetSize() const;

	protected:
		WeakPtr<Tilemap> _tilemap;
		Vector3 _position;
		IntVector3 _index;
		IntVector3 _size;
	};
}