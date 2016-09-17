#include "ObjectLayerFlags.h"

namespace uut
{
	UUT_ENUMFLAG_IMPLEMENT(ObjectLayerFlags)
	{
		RegisterValues(
			"Enabled", ObjectLayerFlag::Enabled,
			"Visibled", ObjectLayerFlag::Visibled,
			"Blocked", ObjectLayerFlag::Blocked);
	}
}