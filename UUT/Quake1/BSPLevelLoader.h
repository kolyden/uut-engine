#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class BSPLevel;

	class BSPLevelLoader : public ResourceLoaderImpl<BSPLevel>
	{
		UUT_OBJECT(uut, BSPLevelLoader, ResourceLoader)
	public:
		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}