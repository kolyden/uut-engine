#pragma once
#include "TilemapLayer.h"

namespace uut
{
	class ObjectLayer;

	class ObjectLayerItem : public RefCounted
	{
	public:
		ObjectLayerItem() : _zorder(0) {}

		void SetPosition(const IntVector2& position) { _position = position; }

		virtual void Update(float deltaTime) {}
		virtual void Draw(Graphics* graphics) const {}

	protected:
		IntVector2 _position;
		int _zorder;
		WeakPtr<ObjectLayer> _layer;

		friend class ObjectLayer;
	};

	class ObjectLayer : public TilemapLayer
	{
		UUT_OBJECT(ObjectLayer, TilemapLayer)
	public:
		ObjectLayer();

		void AddItem(const IntVector2& position, ObjectLayerItem* item);

		void SetSize(const IntVector2& size) override;
		void Update(float deltaTime) override;
		void DrawLayer(Graphics* graphics) const override;

	protected:
		List<SharedPtr<ObjectLayerItem>> _items;
	};
}