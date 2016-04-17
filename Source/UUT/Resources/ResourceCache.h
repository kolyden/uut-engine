#pragma once
#include <Core/Module.h>
#include <Core/Collections/Dictionary.h>
#include <Core/IO/Path.h>

namespace uut
{
	class ResourceLoader;
	class Resource;

	struct ResourceItem : RefCounted
	{
		Path _path;
		SharedPtr<Resource> _data;
	};

	struct ResourceGroup : RefCounted
	{
		Dictionary<Path, SharedPtr<ResourceItem>> _items;
		List<SharedPtr<ResourceLoader>> _loaders;
	};

	class ResourceCache : public Module
	{
		UUT_MODULE(ResourceCache, Module)
	public:
		ResourceCache();
		virtual ~ResourceCache();

		bool AddResource(Resource* resource, const Path& path);
		
		Resource* Find(const Type* type, const Path& path) const;
		Resource* Load(const Type* type, const Path& path, bool silent = false) const;

		void AddLoader(ResourceLoader* loader);

		ResourceGroup* FindGroup(const Type* type) const;
		ResourceItem* FindItem(const Type* type, const Path& path) const;

		template<class C>C* Find(const Path& path) const { return static_cast<C*>(Find(typeof<C>(), path)); }
		template<class C>C* Load(const Path& path, bool silent = false) { return static_cast<C*>(Load(typeof<C>(), path, silent)); }
		template<class C>ResourceGroup* FindGroup() const { return static_cast<C*>(FindGroup(typeof<C>())); }
		template<class C>ResourceItem* FindItem(const Path& path) const { return static_cast<C*>(FindItem(typeof<C>(), path)); }

	protected:
		Dictionary<const Type*, SharedPtr<ResourceGroup>> _groups;

		ResourceGroup* CreateGroup(const Type* type);
		ResourceItem* CreateItem(const Type* type, const Path& path);
	};
}