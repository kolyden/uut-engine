#pragma once
#include <Core/EnumFlags.h>

namespace uut
{
	enum class FieldAttribute
	{
		Public,
		Private,
		Static,
		NotSerialized,
	};
	UUT_ENUMFLAG(uut, FieldAttributes, FieldAttribute)
}