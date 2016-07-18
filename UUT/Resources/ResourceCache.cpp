#include "ResourceCache.h"
#include <Core/IO/StreamContainer.h>
#include "Resource.h"
#include "ResourceLoader.h"
#include <Core/Debug.h>
#include "ResourceLoaderAttribute.h"

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

	void ResourceCache::AddContainer(const SharedPtr<StreamContainer>& container)
	{
		if (!container)
			return;

		_containers.Insert(0, container);
	}

	bool ResourceCache::AddResource(const SharedPtr<Resource>& resource, const Path& path)
	{
		if (resource == nullptr)
			return false;

		resource->_resourcePath = path;
		_groups[resource->GetType()][path.GetHash()] = resource;
		return true;
	}

	SharedPtr<Resource> ResourceCache::Find(const Type* type, const Path& path) const
	{
		if (type == nullptr || path.IsEmpty())
			return nullptr;

		auto it = _groups.Find(type);
		if (it == _groups.End())
			return nullptr;

		auto jt = it->second.Find(path.GetHash());
		if (jt == it->second.End())
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

		for (auto& container : _containers)
		{
			auto stream = container->Open(path, FileMode::OpenRead);
			if (stream == nullptr)
				continue;

			for (auto& loader : it->second)
			{
				resource = loader->Load(stream);
				if (!resource)
					continue;

				resource->_resourcePath = path;
				_groups[type][path.GetHash()] = resource;
				return resource;
			}
		}

		if (!silent)
			Debug::LogWarning("Can't load '%s' from '%s'", type->GetName(), path.GetFullPath().GetData());

		return nullptr;
	}

	const ResourceCache::ResourceDict& ResourceCache::GetResources(const Type* type) const
	{
		auto it = _groups.Find(type);
		return it != _groups.End() ? it->second : ResourceDict::Empty;
	}

	void ResourceCache::AddLoader(const SharedPtr<ResourceLoader>& loader)
	{
		if (loader == nullptr)
			return;

		_loaders[loader->GetResourceType()] << loader;
	}

	bool ResourceCache::OnInit()
	{
		if (!Super::OnInit())
			return false;

		auto list = Attribute::GetAttributes<ResourceLoaderAttribute>();
		for (auto it : list)
		{
			auto type = Context::GetAttributeAttach(it);
			if (!type->IsDerived<ResourceLoader>())
				continue;

			auto loader = type->CreateObject<ResourceLoader>();
			if (!loader)
				continue;

			AddLoader(loader);
		}

		return true;
	}
}
