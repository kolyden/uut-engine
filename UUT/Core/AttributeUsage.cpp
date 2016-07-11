#include "AttributeUsage.h"

namespace uut
{	
	UUT_OBJECT_IMPLEMENT(AttributeUsage)
	{
		internalType->AddAttribute(new AttributeUsage(AttributeTarget::Attribute));
	}

	AttributeUsage::AttributeUsage(AttributeTarget target, bool allowMultiple /*= false*/, bool inherited /*= true*/)
		: _target(target)
		, _allowMultiple(allowMultiple)
		, _inherited(inherited)
	{
	}
}