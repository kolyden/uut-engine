#include "MemberType.h"

namespace uut
{
	UUT_ENUM_IMPLEMENT(MemberType)
	{
		RegisterValues(
			"Constructor", MemberType::Constructor,
			"Converter", MemberType::Converter,
			"Event", MemberType::Event,
			"Method", MemberType::Method,
			"Property", MemberType::Property);
	}
}