#pragma once
#include <Resources/ResourceLoader.h>
#include <Resources/DataObject.h>

namespace uut
{
	class DataObjectLoader : public ResourceLoaderImpl<DataObject>
	{
		UUT_OBJECT(uut, DataObjectLoader, ResourceLoader)
	public:
		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}