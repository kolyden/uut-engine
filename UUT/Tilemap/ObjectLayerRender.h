#pragma once
#include "TilemapRender.h"

namespace uut
{
	class ObjectLayer;

	class ObjectLayerRender : public TilemapRender
	{
		UUT_OBJECT(ObjectLayerRender, TilemapRender)
	public:
		ObjectLayerRender();

		void SetObjectLayer(ObjectLayer* layer);
		ObjectLayer* GetObjectLayer() const;

		virtual	void Draw(Graphics* graphics) const override;

	protected:
		WeakPtr<ObjectLayer> _objectLayer;
	};
}