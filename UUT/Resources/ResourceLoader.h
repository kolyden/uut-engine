#pragma once
#include <Core/Object.h>

namespace uut
{
	class Stream;
	class Resource;

	class ResourceLoader : public Object
	{
		UUT_OBJECT(uut, ResourceLoader, Object)
	public:
		ResourceLoader();
		virtual ~ResourceLoader();

		virtual SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) = 0;
		virtual const Type* GetResourceType() const = 0;
	};

	template<class T>
	class ResourceLoaderImpl : public ResourceLoader
	{
	public:
		const Type* GetResourceType() const override { return TypeOf<T>(); }
	};
}