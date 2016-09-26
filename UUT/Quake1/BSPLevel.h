#pragma once
#include <Resources/Resource.h>
#include <Core/Collections/Dictionary.h>
#include <Core/HashString.h>

namespace uut
{
	class Mesh;
	class Texture2D;

	class BSPLevel : public Resource
	{
		UUT_OBJECT(uut, BSPLevel, Resource)
	public:
		const List<SharedPtr<Mesh>>& GetModels() const { return _models; }
		const Dictionary<HashString, SharedPtr<Texture2D>>& GetTextures() const { return _textures; }

	protected:
		List<SharedPtr<Mesh>> _models;
		Dictionary<HashString, SharedPtr<Texture2D>> _textures;

		friend class BSPLevelLoader;
	};
}