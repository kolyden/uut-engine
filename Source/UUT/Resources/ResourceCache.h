#pragma once
#include <Core/Module.h>

namespace uut
{
	class ResourceCache : public Module
	{
		UUT_MODULE(ResourceCache, Module)
	public:
		ResourceCache();
		virtual ~ResourceCache();
	};
}