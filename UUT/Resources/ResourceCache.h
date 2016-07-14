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
		typedef Dictionary<size_t, SharedPtr<Resource>> ResourceDict;

		ResourceCache();
		virtual ~ResourceCache();

		bool AddResource(const SharedPtr<Resource>& resource, const Path& path);
		
		SharedPtr<Resource> Find(const Type* type, const Path& path) const;
		SharedPtr<Resource> Load(const Type* type, const Path& path, bool silent = false);
		const ResourceDict& GetResources(const Type* type) const;

		void AddLoader(const SharedPtr<ResourceLoader>& loader);

		template<class C, class = typename std::enable_if<std::is_base_of<Resource, C>::value, void>::type>
		SharedPtr<C> Find(const Path& path) const { return StaticCast<C>(Find(TypeOf<C>(), path)); }

		template<class C, class = typename std::enable_if<std::is_base_of<Resource, C>::value, void>::type>
		SharedPtr<C> Load(const Path& path, bool silent = false) { return StaticCast<C>(Load(TypeOf<C>(), path, silent)); }

		template<class C, class = typename std::enable_if<std::is_base_of<Resource, C>::value, void>::type>
		const ResourceDict& GetResources() const { return GetResources(TypeOf<Resource>()); }

	protected:
		Dictionary<const Type*, List<SharedPtr<ResourceLoader>>> _loaders;
		Dictionary<const Type*, ResourceDict> _groups;

		bool OnInit() override;
	};
}