#include "ObjectLayerItem.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(ObjectLayerItem)
	{		
	}

	ObjectLayerItem::ObjectLayerItem()
		: _zorder(0)
	{		
	}

	void ObjectLayerItem::SetPosition(const IntVector2& position)
	{
		_position = position;
	}

	const IntVector2& ObjectLayerItem::GetPosition() const
	{
		return _position;
	}

	void ObjectLayerItem::SetFlags(const ObjectLayerFlags& flags)
	{
		_flags = flags;
	}

	const ObjectLayerFlags& ObjectLayerItem::GetFlags() const
	{
		return _flags;
	}
}