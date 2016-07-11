#pragma once
#include <Resources/ResourceLoader.h>

namespace uut
{
	class Renderer;

	class Texture2DLoader : public ResourceLoader
	{
		UUT_OBJECT(Texture2DLoader, ResourceLoader)
	public:
		explicit Texture2DLoader();

		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
		const Type* GetResourceType() const override;
	};
}