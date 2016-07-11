#pragma once
#include <Core/Module.h>
#include <Core/Collections/Dictionary.h>
#include <Core/IO/Path.h>

namespace uut
{
	class Resource;
	class ResourceLoader;

	struct ResourceGroup
	{
		Dictionary<Path, SharedPtr<Resource>> _items;
	};

	class ResourceCache : public Module
	{
		UUT_MODULE(ResourceCache, Module)
	public:
		ResourceCache();
		virtual ~ResourceCache();

		bool AddResource(const SharedPtr<Resource>& resource, const Path& path);
		
		SharedPtr<Resource> Find(const Type* type, const Path& path) const;
		SharedPtr<Resource> Load(const Type* type, const Path& path, bool silent = false);

		void AddLoader(const SharedPtr<ResourceLoader>& loader);

		template<class C>SharedPtr<C> Find(const Path& path) const { return StaticCast<C>(Find(typeof<C>(), path)); }
		template<class C>SharedPtr<C> Load(const Path& path, bool silent = false) { return StaticCast<C>(Load(typeof<C>(), path, silent)); }

	protected:
		Dictionary<const Type*, List<SharedPtr<ResourceLoader>>> _loaders;
		Dictionary<const Type*, ResourceGroup> _groups;
	};
}