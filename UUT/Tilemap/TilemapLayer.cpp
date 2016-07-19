#include "TilemapLayer.h"
#include "Tilemap.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilemapLayer)
	{}

	TilemapLayer::TilemapLayer()
		: _active(true)
		, _visible(true)
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

	void TilemapLayer::SetVisible(bool visible)
	{
		_visible = visible;
	}

	bool TilemapLayer::IsVisible() const
	{
		return _visible;
	}

	SharedPtr<Tilemap> TilemapLayer::GetTilemap() const
	{
		return _tilemap.Lock();
	}
}