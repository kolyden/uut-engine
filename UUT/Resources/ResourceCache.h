#pragma once
#include <Core/Module.h>
#include <Core/Collections/Dictionary.h>
#include <Core/IO/Path.h>

namespace uut
{
	class Resource;
	class ResourceLoader;

	struct ResourceItem
	{
		Path _path;
		SharedPtr<Resource> _data;

		ResourceItem();
		~ResourceItem();
	};

	struct ResourceGroup
	{
		Dictionary<Path, SharedPtr<ResourceItem>> _items;
		List<SharedPtr<ResourceLoader>> _loaders;

		ResourceGroup();
		~ResourceGroup();
	};

	class ResourceCache : public Module
	{
		UUT_MODULE(ResourceCache, Module)
	public:
		ResourceCache();
		virtual ~ResourceCache();

		bool AddResource(SharedPtr<Resource> resource, const Path& path);
		
		SharedPtr<Resource> Find(const Type* type, const Path& path) const;
		SharedPtr<Resource> Load(const Type* type, const Path& path, bool silent = false) const;

		void AddLoader(SharedPtr<ResourceLoader> loader);

		SharedPtr<ResourceGroup> FindGroup(const Type* type) const;
		SharedPtr<ResourceItem> FindItem(const Type* type, const Path& path) const;

		template<class C>SharedPtr<C> Find(const Path& path) const { return StaticCast<C>(Find(typeof<C>(), path)); }
		template<class C>SharedPtr<C> Load(const Path& path, bool silent = false) { return StaticCast<C>(Load(typeof<C>(), path, silent)); }
		template<class C>SharedPtr<ResourceGroup> FindGroup() const { return StaticCast<C>(FindGroup(typeof<C>())); }
		template<class C>SharedPtr<ResourceItem> FindItem(const Path& path) const { return StaticCast<C>(FindItem(typeof<C>(), path)); }

	protected:
		Dictionary<const Type*, SharedPtr<ResourceGroup>> _groups;

		SharedPtr<ResourceGroup> CreateGroup(const Type* type);
		SharedPtr<ResourceItem> CreateItem(const Type* type, const Path& path);
	};
}