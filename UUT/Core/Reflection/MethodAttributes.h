#pragma once
#include <Core/EnumFlags.h>

namespace uut
{
	enum class MethodAttribute
	{
		None,
		Private = 1,
		Public = 2,
		Static = 4,
	};
	UUT_ENUMFLAG(MethodAttributes, MethodAttribute)
}