#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class Quake1ModelLoader : public ResourceLoader
	{
		UUT_OBJECT(eng, Quake1ModelLoader, ResourceLoader)
	public:
		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
		const Type* GetResourceType() const override;
	};
}