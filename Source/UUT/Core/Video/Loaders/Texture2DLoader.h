#pragma once
#include <Core/Resources/ResourceLoader.h>

namespace uut
{
	class Renderer;

	class Texture2DLoader : public ResourceLoader
	{
		UUT_OBJECT(Texture2DLoader, ResourceLoader)
	public:
		explicit Texture2DLoader(Renderer* renderer);
		virtual ~Texture2DLoader();

		SharedPtr<Resource> Load(Stream* stream) override;

	protected:
		SharedPtr<Renderer> _renderer;
	};
}