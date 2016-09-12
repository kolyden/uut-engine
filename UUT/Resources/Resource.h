#pragma once
#include <Core/Object.h>
#include <Core/IO/Path.h>

namespace uut
{
	class Resource : public Object
	{
		UUT_OBJECT(uut, Resource, Object)
	public:
		Resource();
		virtual ~Resource();

		String ToString() override;
		const Path& GetResourcePath() const { return _resourcePath; }

	private:
		Path _resourcePath;

		friend class ResourceCache;
	};
}
