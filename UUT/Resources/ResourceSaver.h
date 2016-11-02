#pragma once
#include <Core/Object.h>

namespace uut
{
	class Stream;
	class Resource;

	class ResourceSaver : public Object
	{
		UUT_OBJECT(uut, ResourceSaver, Object)
	public:
		virtual bool Save(const SharedPtr<Resource>& resource, const SharedPtr<Stream>& stream) = 0;
		virtual const Type* GetResourceType() const = 0;
	};

	template<class T>
	class ResourceSaverImpl : public ResourceSaver
	{
	public:
		const Type* GetResourceType() const override { return TypeOf<T>(); }
	};
}