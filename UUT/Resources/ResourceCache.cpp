#include "ResourceCache.h"
#include <Core/IO/StreamContainer.h>
#include "Resource.h"
#include "ResourceLoader.h"
#include "ResourceSaver.h"
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
		InternalAddResource(resource);
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
				InternalAddResource(resource);
				return resource;
			}
		}

		if (!silent)
			Debug::LogWarning("Can't load '%s' from '%s'", type->GetName(), path.GetFullPath().GetData());

		return nullptr;
	}

	bool ResourceCache::Save(const SharedPtr<Resource>& resource, const Path& path, bool silent /*= false*/)
	{
		if (!resource || path.IsEmpty())
			return false;

		if (_containers.IsEmpty())
		{
			if (!silent)
				Debug::LogWarning("Can save resource, no container added");
			return false;
		}

		const Type* type = resource->GetType();
		auto jt = _savers.Find(type);
		if (jt == _savers.End())
		{
			if (!silent)
				Debug::LogWarning("Can save resource: no saver for %s", type->GetFullName());

			return false;
		}

		for (auto it = _containers.RBegin(); it != _containers.REnd(); ++it)
		{
			auto stream = (*it)->Open(path, FileMode::Create);
			if (!stream)
				continue;

			for (auto& saver : jt->second)
			{
				if (saver->Save(resource, stream))
					return true;
			}
		}

		return false;
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

	void ResourceCache::AddSaver(const SharedPtr<ResourceSaver>& saver)
	{
		if (saver)
			_savers[saver->GetResourceType()] << saver;
	}

// 	bool ResourceCache::OnInit()
// 	{
// 		if (!Super::OnInit())
// 			return false;
// 
// 		auto list = Context::GetAttributes<ResourceLoaderAttribute>();
// 		for (auto it : list)
// 		{
// 			auto type = it.first;
// 			if (!type->IsDerived<ResourceLoader>())
// 				continue;
// 
// 			auto loader = type->CreateObject<ResourceLoader>();
// 			if (!loader)
// 				continue;
// 
// 			AddLoader(loader);
// 		}
// 
// 		return true;
// 	}

	void ResourceCache::InternalAddResource(const SharedPtr<Resource>& resource)
	{
		const size_t hash = resource->GetResourcePath().GetHash();
		for (auto type = resource->GetType(); type != TypeOf<Resource>(); type = type->GetBaseType())
			_groups[type][hash] = resource;
	}
}