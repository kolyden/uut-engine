#include "ResourceCache.h"
#include <Core/IO/File.h>
#include <Core/IO/FileStream.h>
#include "Resource.h"
#include "ResourceLoader.h"

namespace uut
{
	ResourceItem::ResourceItem()
	{
	}

	ResourceItem::~ResourceItem()
	{
	}

	ResourceGroup::ResourceGroup()
	{
	}

	ResourceGroup::~ResourceGroup()
	{
	}

	////////////////////////////////////////////////////////////////////////////
	UUT_MODULE_IMPLEMENT(ResourceCache)
	{}

	ResourceCache::ResourceCache()
	{
	}

	ResourceCache::~ResourceCache()
	{
	}

	bool ResourceCache::AddResource(SharedPtr<Resource> resource, const Path& path)
	{
		if (resource == nullptr)
			return false;

		if (Find(resource->GetType(), path) != nullptr)
			return false;

		auto item = CreateItem(resource->GetType(), path);
		item->_data = resource;
		return true;
	}

	SharedPtr<Resource> ResourceCache::Find(const Type* type, const Path& path) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto item = FindItem(type, path);
		return item != nullptr ? item->_data.Get() : nullptr;
	}

	SharedPtr<Resource> ResourceCache::Load(const Type* type, const Path& path, bool silent /*= false*/) const
	{
		return nullptr;
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto item = FindItem(type, path);
		if (item != nullptr)
			return item->_data;

		auto group = FindGroup(type);
		if (group == nullptr)
			return nullptr;

		auto stream = DynamicCast<Stream>(File::OpenRead(path));
		if (stream == nullptr)
			return nullptr;

		for (auto& loader : group->_loaders)
		{
			auto resource = loader->Load(stream);
			if (!resource)
				continue;

			item = SharedPtr<ResourceItem>::Make();
			item->_path = path;
			item->_data = resource;
			group->_items[path] = item;
			return resource;
		}

		return nullptr;
	}

	void ResourceCache::AddLoader(SharedPtr<ResourceLoader> loader)
	{
		if (loader == nullptr)
			return;

		auto group = CreateGroup(loader->GetResourceType());
		group->_loaders << loader;
	}

	SharedPtr<ResourceGroup> ResourceCache::FindGroup(const Type* type) const
	{
		if (type == nullptr)
			return nullptr;

		auto it = _groups.Find(type);
		return it != _groups.End() ? it->second.Get() : nullptr;
	}

	SharedPtr<ResourceItem> ResourceCache::FindItem(const Type* type, const Path& path) const
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
	SharedPtr<ResourceGroup> ResourceCache::CreateGroup(const Type* type)
	{
		auto it = _groups.Find(type);
		if (it != _groups.End())
			return it->second;

		auto group = SharedPtr<ResourceGroup>::Make();
		_groups[type] = group;
		return group;
	}

	SharedPtr<ResourceItem> ResourceCache::CreateItem(const Type* type, const Path& path)
	{
		auto group = CreateGroup(type);

		auto it = group->_items.Find(path);
		if (it != group->_items.End())
			return it->second;

		auto item = SharedPtr<ResourceItem>::Make();
		item->_path = path;
		group->_items[path] = item;
		return item;
	}
}