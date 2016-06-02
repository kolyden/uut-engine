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
		virtual bool IsBlocked() const { return true; }

	protected:
		IntVector2 _position;
		int _zorder;
		WeakPtr<ObjectLayer> _layer;

		virtual void OnInit() {}

		friend class ObjectLayer;
	};

	////////////////////////////////////////////////////////////////////////////
	class ObjectLayer : public TilemapLayer
	{
		UUT_OBJECT(ObjectLayer, TilemapLayer)
	public:
		ObjectLayer();

		void AddItem(const IntVector2& position, ObjectLayerItem* item);
		ObjectLayerItem* GetItem(const IntVector2& position) const;

		void SetSize(const IntVector2& size) override;
		void Update(float deltaTime) override;
		void DrawLayer(Graphics* graphics) const override;

	protected:
		List<SharedPtr<ObjectLayerItem>> _items;
	};
}