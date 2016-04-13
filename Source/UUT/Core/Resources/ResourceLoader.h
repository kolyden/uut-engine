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

		virtual SharedPtr<Resource> Load(Stream* stream) = 0;
	};
}