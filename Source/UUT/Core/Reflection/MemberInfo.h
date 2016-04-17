#pragma once
#include <Core/String.h>
#include "MemberType.h"

namespace uut
{
	class MemberInfo
	{
	public:
		MemberInfo();
		virtual ~MemberInfo();

		virtual MemberType GetMemberType() const = 0;
		virtual const String& GetName() const = 0;

	protected:
		String _name;
	};
}