#pragma once
#include <Core/Object.h>

namespace uut
{
	class Stream;
	class Resource;

	class ResourceLoader : public Object
	{
		UUT_OBJECT(ResourceLoader, Object)
	public:
		ResourceLoader();
		virtual ~ResourceLoader();

		virtual SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) = 0;
		virtual const Type* GetResourceType() const = 0;
	};
}