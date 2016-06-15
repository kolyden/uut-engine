#include "ObjectLayerRender.h"
#include "ObjectLayer.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(ObjectLayerRender)
	{}

	ObjectLayerRender::ObjectLayerRender()
	{}

	void ObjectLayerRender::SetObjectLayer(ObjectLayer* layer)
	{
		_objectLayer = layer;
	}

	ObjectLayer* ObjectLayerRender::GetObjectLayer() const
	{
		return _objectLayer;
	}

	void ObjectLayerRender::Draw(Graphics* graphics) const
	{
		if (_objectLayer == nullptr)
			return;

		for (auto& item : _objectLayer->GetItems())
			item->Draw(graphics);
	}
}