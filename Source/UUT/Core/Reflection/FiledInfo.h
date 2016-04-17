#pragma once
#include "MemberInfo.h"
#include "FieldAttribute.h"

namespace uut
{
	class FieldInfo : public MemberInfo
	{
	public:
		explicit FieldInfo(const String& name, FieldAttribute attributes);

		MemberType GetMemberType() const override;
		const String& GetName() const override;

		FieldAttribute GetAttributes() const { return _attributes; }

		bool IsPublic() const;
		bool IsPrivate() const;
		bool IsStatic() const;

	protected:
		String _name;
		FieldAttribute _attributes;
	};
}