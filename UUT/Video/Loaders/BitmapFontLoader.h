#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class ResourceCache;

	class BitmapFontLoader : public ResourceLoader
	{
		UUT_OBJECT(BitmapFontLoader, ResourceLoader)
	public:
		explicit BitmapFontLoader(ResourceCache* cache);

		virtual SharedPtr<Resource> Load(Stream* stream) override;
		virtual const Type* GetResourceType() const override;

	protected:
		WeakPtr<ResourceCache> _cache;
	};
}