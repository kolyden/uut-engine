#pragma once
#include <Core/Object.h>

namespace uut
{
	class Stream;
	class Resource;

	class ResourceLoader : public Object
	{
	public:
		virtual SharedPtr<Resource> Load(Stream* stream) = 0;
	};
}