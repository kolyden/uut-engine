#include "ObjectLayerRender.h"
#include "ObjectLayer.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(ObjectLayerRender)
	{}

	ObjectLayerRender::ObjectLayerRender()
	{}

	void ObjectLayerRender::SetObjectLayer(SharedPtr<ObjectLayer> layer)
	{
		_objectLayer = layer;
	}

	SharedPtr<ObjectLayer> ObjectLayerRender::GetObjectLayer() const
	{
		return _objectLayer.Lock();
	}

	void ObjectLayerRender::Draw(Graphics* graphics) const
	{
		if (auto layer = _objectLayer.Lock())
		{
			for (auto& item : layer->GetItems())
				item->Draw(graphics);
		}
	}
}