#pragma once
#include "Resources\Resource.h"

namespace uut
{
	class Texture2D;
	class Mesh;

	class Quake1Model : public Resource
	{
		UUT_OBJECT(uut, Quake1Model, Resource)
	public:

		const List<SharedPtr<Texture2D>>& GetSkins() const { return _skins; }
		const List<SharedPtr<Mesh>>& GetFrames() const { return _frames; }

	protected:
		List<SharedPtr<Texture2D>> _skins;
		List<SharedPtr<Mesh>> _frames;

		friend class Quake1ModelLoader;
	};
}