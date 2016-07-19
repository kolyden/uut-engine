#pragma once
#include "TilemapLayer.h"

namespace uut
{
	class ObjectLayerItem;

	class ObjectLayer : public TilemapLayer
	{
		UUT_OBJECT(ObjectLayer, TilemapLayer)
	public:
		typedef List<SharedPtr<ObjectLayerItem>> ObjectLayerItemList;

		ObjectLayer();

		void AddItem(const IntVector2& position, const SharedPtr<ObjectLayerItem>& item);
		const ObjectLayerItemList& GetItems() const;

		const SharedPtr<ObjectLayerItem>& GetItemAt(const IntVector2& position) const;

		template<class T, typename... Args,
			class = typename std::enable_if<std::is_constructible<ObjectLayerItem, Args...>::value, void>::type,
			class = typename std::enable_if<std::is_base_of<ObjectLayerItem, T>::value, void>::type>
		SharedPtr<T> CreateItem(const IntVector2& position, Args&&... args)
		{
			auto item = MakeShared<T>(std::forward<Args>(args)...);
			AddItem(position, item);
			return item;
		}

	protected:
		ObjectLayerItemList _items;

		void OnUpdate(float deltaTime) override;
		void OnRender() const override;
	};
}