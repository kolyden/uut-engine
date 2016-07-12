#include "AttributeUsage.h"

namespace uut
{
	UUT_ENUMFLAG_IMPLEMENT(AttributeTargets, AttributeTarget)
	{
		RegisterValues(
			"Method", AttributeTarget::Method,
			"Class", AttributeTarget::Class,
			"Property", AttributeTarget::Property,
			"Event", AttributeTarget::Event,
			"Attribute", AttributeTarget::Attribute,
			"All", AttributeTarget::All);
	}

	UUT_OBJECT_IMPLEMENT(AttributeUsage)
	{
		internalType->AddAttribute(new AttributeUsage(AttributeTarget::Attribute, false, true));
	}

	AttributeUsage::AttributeUsage(AttributeTargets targets, bool allowMultiple /*= false*/, bool inherited /*= true*/)
		: _targets(targets)
		, _allowMultiple(allowMultiple)
		, _inherited(inherited)
	{
	}

	String AttributeUsage::ToString()
	{
		return Super::ToString() + "(targets:" + _targets.ToString() + ")";
	}
}