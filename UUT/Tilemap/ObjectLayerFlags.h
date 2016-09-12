#pragma once
#include <Core/EnumFlags.h>

namespace uut
{
	enum class ObjectLayerFlag
	{
		None = 0,
		Enabled = 1,
		Visibled = 2,
		Blocked = 4,
	};
	UUT_ENUMFLAG(uut, ObjectLayerFlags, ObjectLayerFlag)
}