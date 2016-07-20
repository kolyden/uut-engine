#pragma once
#include <Core/Math/IntVector2.h>
#include <Core/Object.h>
#include "ObjectLayerFlags.h"

namespace uut
{
	class ObjectLayer;

	class ObjectLayerItem : public Object
	{
		UUT_OBJECT(ObjectLayerItem, Object)
	public:
		ObjectLayerItem();

		void SetPosition(const IntVector2& position);
		const IntVector2& GetPosition() const;

		void SetFlags(const ObjectLayerFlags& flags);
		const ObjectLayerFlags& GetFlags() const;

		bool IsBlocked() const { return _flags.HasFlag(ObjectLayerFlag::Blocked); }

	protected:
		IntVector2 _position;
		int _zorder;
		WeakPtr<ObjectLayer> _layer;
		ObjectLayerFlags _flags;

		virtual void OnInit() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() const {}

		friend class ObjectLayer;
	};
}