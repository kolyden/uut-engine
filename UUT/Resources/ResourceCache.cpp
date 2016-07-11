#include "ResourceCache.h"
#include <Core/IO/File.h>
#include <Core/IO/FileStream.h>
#include "Resource.h"
#include "ResourceLoader.h"
#include <Core/Debug.h>

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

	bool ResourceCache::AddResource(const SharedPtr<Resource>& resource, const Path& path)
	{
		if (resource == nullptr)
			return false;

		resource->_resourcePath = path;
		_groups[resource->GetType()]._items[path] = resource;
		return true;
	}

	SharedPtr<Resource> ResourceCache::Find(const Type* type, const Path& path) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto it = _groups.Find(type);
		if (it == _groups.End())
			return nullptr;

		auto jt = it->second._items.Find(path);
		if (jt == it->second._items.End())
			return nullptr;

		return jt->second;
	}

	SharedPtr<Resource> ResourceCache::Load(const Type* type, const Path& path, bool silent /*= false*/)
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto resource = Find(type, path);
		if (resource)
			return resource;

		auto it = _loaders.Find(type);
		if (it == _loaders.End())
			return nullptr;

		auto stream = DynamicCast<Stream>(File::OpenRead(path));
		if (stream == nullptr)
			return nullptr;

		for (auto& loader : it->second)
		{
			resource = loader->Load(stream);
			if (!resource)
				continue;

			resource->_resourcePath = path;
			_groups[type]._items[path] = resource;
			return resource;
		}

		if (!silent)
			Debug::LogWarning("Can't load '%s' from '%s'", type->GetName(), path.GetFullPath().GetData());

		return nullptr;
	}

	void ResourceCache::AddLoader(const SharedPtr<ResourceLoader>& loader)
	{
		if (loader == nullptr)
			return;

		_loaders[loader->GetResourceType()] << loader;
	}
}
