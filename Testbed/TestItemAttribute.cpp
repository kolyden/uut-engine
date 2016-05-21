#include "TestItemAttribute.h"
#include <Core/AttributeUsage.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TestItemAttribute)
	{
		Attribute::AddAttribute(internalType, new AttributeUsage(AttributeTarget::Attribute));
	}

	TestItemAttribute::TestItemAttribute(TestCategory category, const String& title)
		: _category(category)
		, _title(title)
	{
	}
}