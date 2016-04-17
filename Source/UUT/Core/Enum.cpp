#include "Enum.h"
#include <Core/Reflection/Type.h>

namespace uut
{
	String Enum::ToString(const Type* type, int val)
	{
// 		if (type == nullptr || !type->IsEnum)
			return String::Empty;
	}

	bool Enum::TryParse(const Type* type, const String& str, int& val)
	{
// 		if (type == nullptr || str.IsEmpty() || !type->IsEnum())
			return false;
	}
}