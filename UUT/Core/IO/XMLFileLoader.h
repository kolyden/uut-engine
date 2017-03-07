#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class XMLFileLoader : public ResourceLoader
	{
		UUT_OBJECT(uut, XMLFileLoader, ResourceLoader)
	public:
		virtual SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
		virtual const Type* GetResourceType() const override;
	};
}