#include "ObjectLayer.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(ObjectLayer)
	{}

	ObjectLayer::ObjectLayer()
	{
	}

	void ObjectLayer::AddItem(const IntVector2& position, ObjectLayerItem* item)
	{
		if (item == nullptr)
			return;

		_items << SharedPtr<ObjectLayerItem>(item);
		item->_position = position;
		item->_layer = this;
		item->OnInit();
	}

	ObjectLayerItem* ObjectLayer::GetItem(const IntVector2& position) const
	{
		for (auto& item : _items)
		{
			if (item->_position == position)
				return item;
		}

		return nullptr;
	}

	void ObjectLayer::SetSize(const IntVector2& size)
	{
	}

	void ObjectLayer::Update(float deltaTime)
	{
		for (auto& item : _items)
			item->Update(deltaTime);
	}

	void ObjectLayer::DrawLayer(Graphics* graphics) const
	{
		for (auto& item : _items)
			item->Draw(graphics);
	}
}