#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class ResourceCache;

	class BitmapFontLoader : public ResourceLoader
	{
		UUT_OBJECT(BitmapFontLoader, ResourceLoader)
	public:
		BitmapFontLoader();

		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
		const Type* GetResourceType() const override;
	};
}