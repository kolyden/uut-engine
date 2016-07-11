#include "Resource.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Resource)
	{}

	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
	}

	String Resource::ToString()
	{
		if (_resourcePath.IsEmpty())
			return Super::ToString();

		return Super::ToString() + " (" + _resourcePath.GetFullPath() + ")";
	}
}