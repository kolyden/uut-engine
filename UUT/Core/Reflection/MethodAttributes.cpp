#include "MethodAttributes.h"

namespace uut
{
	UUT_ENUMFLAG_IMPLEMENT(MethodAttributes, MethodAttribute)
	{
		RegisterValues(
			"Private", MethodAttribute::Private,
			"Public", MethodAttribute::Public,
			"Static", MethodAttribute::Static);
	}
}