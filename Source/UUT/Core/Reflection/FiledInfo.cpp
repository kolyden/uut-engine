#include "FiledInfo.h"

namespace uut
{
	FieldInfo::FieldInfo(const String& name, FieldAttribute attributes)
		: _name(name)
		, _attributes(attributes)
	{
	}

	MemberType FieldInfo::GetMemberType() const
	{
		return MemberType::Field;
	}

	bool FieldInfo::IsPublic() const
	{
		return _attributes == FieldAttribute::Public;
	}

	bool FieldInfo::IsPrivate() const
	{
		return _attributes == FieldAttribute::Private;
	}

	bool FieldInfo::IsStatic() const
	{
		return _attributes == FieldAttribute::Static;
	}

	const String& FieldInfo::GetName() const
	{
		return _name;
	}
}