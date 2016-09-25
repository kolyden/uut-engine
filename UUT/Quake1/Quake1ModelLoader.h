#pragma once
#include <Resources/ResourceLoader.h>
#include "Quake1Model.h"

namespace uut
{
	class Quake1ModelLoader : public ResourceLoaderImpl<Quake1Model>
	{
		UUT_OBJECT(eng, Quake1ModelLoader, ResourceLoader)
	public:
		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}