#include "ObjectLayer.h"
#include "ObjectLayerItem.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(ObjectLayer)
	{}

	ObjectLayer::ObjectLayer()
	{
	}

	void ObjectLayer::AddItem(const IntVector2& position, const SharedPtr<ObjectLayerItem>& item)
	{
		if (!item)
			return;

		_items << item;
		item->_position = position;
		item->_layer = GetSharedThis();
		item->OnInit();
	}

	const SharedPtr<ObjectLayerItem>& ObjectLayer::GetItemAt(const IntVector2& position) const
	{
		for (auto& item : _items)
		{
			if (item->_position == position)
				return item;
		}

		return SharedPtr<ObjectLayerItem>::Empty;
	}

	const ObjectLayer::ObjectLayerItemList& ObjectLayer::GetItems() const
	{
		return _items;
	}

	void ObjectLayer::OnUpdate(float deltaTime)
	{
		for (auto& item : _items)
			item->OnUpdate(deltaTime);
	}

	void ObjectLayer::OnRender() const
	{
		for (auto& item : _items)
			item->OnRender();
	}
}