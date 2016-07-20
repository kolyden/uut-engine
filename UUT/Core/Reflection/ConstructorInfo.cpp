#include "ConstructorInfo.h"

namespace uut
{	
	MemberType IConstructorInfo::GetMemberType() const
	{
		return MemberType::Constructor;
	}

	const String& IConstructorInfo::GetName() const
	{
		static const String name("Constructor");
		return name;
	}
}