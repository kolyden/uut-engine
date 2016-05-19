#include "ResourceCache.h"
#include <Core/IO/File.h>
#include <Core/IO/FileStream.h>
#include "Resource.h"
#include "ResourceLoader.h"

namespace uut
{
	UUT_MODULE_IMPLEMENT(ResourceCache)
	{}

	ResourceCache::ResourceCache()
	{
	}

	ResourceCache::~ResourceCache()
	{
	}

	bool ResourceCache::AddResource(Resource* resource, const Path& path)
	{
		if (resource == nullptr)
			return false;

		if (Find(resource->GetType(), path) != nullptr)
			return false;

		auto item = CreateItem(resource->GetType(), path);
		item->_data = resource;
		return true;
	}

	Resource* ResourceCache::Find(const Type* type, const Path& path) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto item = FindItem(type, path);
		return item != nullptr ? item->_data.Get() : nullptr;
	}

	Resource* ResourceCache::Load(const Type* type, const Path& path, bool silent /*= false*/) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto item = FindItem(type, path);
		if (item != nullptr)
			return item->_data;

		auto group = FindGroup(type);
		if (group == nullptr)
			return nullptr;

		auto stream = File::OpenRead(path);
		for (auto& loader : group->_loaders)
		{
			auto data = loader->Load(stream);
			if (!data)
				continue;

			item = new ResourceItem();
			item->_path = path;
			item->_data = data;
			group->_items[path] = item;
			return data;
		}

		return nullptr;
	}

	void ResourceCache::AddLoader(ResourceLoader* loader)
	{
		if (loader == nullptr)
			return;

		auto group = CreateGroup(loader->GetResourceType());
		group->_loaders.Add(SharedPtr<ResourceLoader>(loader));
	}

	ResourceGroup* ResourceCache::FindGroup(const Type* type) const
	{
		if (type == nullptr)
			return nullptr;

		auto it = _groups.Find(type);
		return it != _groups.End() ? it->second.Get() : nullptr;
	}

	ResourceItem* ResourceCache::FindItem(const Type* type, const Path& path) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto it = _groups.Find(type);
		if (it == _groups.End())
			return nullptr;

		auto jt = it->second->_items.Find(path);
		if (jt == it->second->_items.End())
			return nullptr;

		return jt->second;
	}

	//////////////////////////////////////////////////////////////////////////////
	ResourceGroup* ResourceCache::CreateGroup(const Type* type)
	{
		SharedPtr<ResourceGroup> group;
		if (_groups.TryGetValue(type, group))
			return group;

		group = new ResourceGroup();
		_groups[type] = group;
		return group;
	}

	ResourceItem* ResourceCache::CreateItem(const Type* type, const Path& path)
	{
		auto group = CreateGroup(type);

		SharedPtr<ResourceItem> item;
		if (group->_items.TryGetValue(path, item))
			return item;

		item = new ResourceItem();
		item->_path = path;
		group->_items[path] = item;
		return item;
	}
}