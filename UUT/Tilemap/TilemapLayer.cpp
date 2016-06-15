#include "TilemapLayer.h"
#include "Tilemap.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilemapLayer)
	{}

	TilemapLayer::TilemapLayer()
		: _active(true)
	{		
	}

	void TilemapLayer::SetName(const String& name)
	{
		_name = name;
	}

	const String& TilemapLayer::GetName() const
	{
		return _name;
	}

	void TilemapLayer::SetActive(bool active)
	{
		_active = active;
	}

	bool TilemapLayer::IsActive() const
	{
		return _active;
	}
}