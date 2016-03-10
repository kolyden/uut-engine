#pragma once
#include <Core/Resources/ResourceLoader.h>

namespace uut
{
	class Renderer;

	class Texture2DLoader : public ResourceLoader
	{
	public:
		explicit Texture2DLoader(Renderer* renderer);

		SharedPtr<Resource> Load(Stream* stream) override;

	protected:
		SharedPtr<Renderer> _renderer;
	};
}