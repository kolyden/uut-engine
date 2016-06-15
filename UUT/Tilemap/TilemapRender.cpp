#include "TilemapRender.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TilemapRender)
	{}

	TilemapRender::TilemapRender()
		: _visible(true)
	{		
	}

	void TilemapRender::SetVisible(bool visible)
	{
		_visible = visible;
	}

	bool TilemapRender::IsVisible() const
	{
		return _visible;
	}
}