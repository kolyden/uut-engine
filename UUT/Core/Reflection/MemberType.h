#pragma once
#include <Core/Enum.h>

namespace uut
{
	enum class MemberType
	{
		Constructor,
		Converter,
		Event,
		Method,
		Property,
	};
	UUT_ENUM(MemberType)
}