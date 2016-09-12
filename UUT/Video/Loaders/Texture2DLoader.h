#pragma once
#include <Resources/ResourceLoader.h>
#include <Video/Texture2D.h>

namespace uut
{
	class Renderer;

	class Texture2DLoader : public ResourceLoaderImpl<Texture2D>
	{
		UUT_OBJECT(uut, Texture2DLoader, ResourceLoader)
	public:
		explicit Texture2DLoader();

		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}