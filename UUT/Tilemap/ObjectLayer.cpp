#include "ObjectLayer.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(ObjectLayer)
	{}

	ObjectLayer::ObjectLayer()
	{
	}

	void ObjectLayer::AddItem(const IntVector2& position, SharedPtr<ObjectLayerItem> item)
	{
		if (!item)
			return;

		_items << item;
		item->_position = position;
		item->_layer = GetSharedThis();
		item->OnInit();
	}

	SharedPtr<ObjectLayerItem> ObjectLayer::GetItem(const IntVector2& position) const
	{
		for (auto& item : _items)
		{
			if (item->_position == position)
				return item;
		}

		return nullptr;
	}

	const ObjectLayerItemList& ObjectLayer::GetItems() const
	{
		return _items;
	}

	void ObjectLayer::SetSize(const IntVector2& size)
	{
	}

	void ObjectLayer::Update(float deltaTime)
	{
		for (auto& item : _items)
			item->Update(deltaTime);
	}
}