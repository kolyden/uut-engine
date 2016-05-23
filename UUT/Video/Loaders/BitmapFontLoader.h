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

		virtual SharedPtr<Resource> Load(Stream* stream) override;
		virtual const Type* GetResourceType() const override;
	};
}