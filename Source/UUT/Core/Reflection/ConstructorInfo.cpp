#include "ConstructorInfo.h"

namespace uut
{	
	const String& ConstructorInfo::GetName() const
	{
		static const String name("Constructor");
		return name;
	}
}