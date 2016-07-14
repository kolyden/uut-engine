#include "ResourceLoaderAttribute.h"
#include <Core/AttributeUsage.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(ResourceLoaderAttribute)
	{
		internalType->AddAttribute(new AttributeUsage(AttributeTarget::Class, false, false));
	}
}