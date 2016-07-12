#pragma once
#include <Resources/ResourceLoader.h>
#include <Video/Font.h>

namespace uut
{
	class ResourceCache;

	class BitmapFontLoader : public ResourceLoaderImpl<Font>
	{
		UUT_OBJECT(BitmapFontLoader, ResourceLoader)
	public:
		BitmapFontLoader();

		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}