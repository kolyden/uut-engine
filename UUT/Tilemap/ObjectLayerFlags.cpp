#include "ObjectLayerFlags.h"

namespace uut
{
	UUT_ENUMFLAG_IMPLEMENT(ObjectLayerFlags, ObjectLayerFlag)
	{
		RegisterValues(
			"Enabled", ObjectLayerFlag::Enabled,
			"Visibled", ObjectLayerFlag::Visibled,
			"Blocked", ObjectLayerFlag::Blocked);
	}
}