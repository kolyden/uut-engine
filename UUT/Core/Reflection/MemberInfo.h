#pragma once
#include <Core/String.h>
#include "MemberType.h"

namespace uut
{
	class IMemberInfo
	{
	public:
		IMemberInfo();
		virtual ~IMemberInfo();

		virtual MemberType GetMemberType() const = 0;
		virtual const String& GetName() const = 0;
	};
}