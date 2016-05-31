#include "TilemapLayer.h"
#include "Tilemap.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilemapLayer)
	{}

	TilemapLayer::TilemapLayer()
		: _visible(true)
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

	void TilemapLayer::SetVisible(bool visible)
	{
		_visible = visible;
	}

	bool TilemapLayer::IsVisible() const
	{
		return _visible;
	}
}