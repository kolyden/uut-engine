#pragma once
#include <Core/String.h>

namespace uut
{
	class Type;

	class Enum
	{
	public:
		static String ToString(const Type* type, int val);
		static bool TryParse(const Type* type, const String& str, int& val);
	};

#define UUT_ENUM(type)

#define UUT_ENUM_IMPLEMENT(type)
}