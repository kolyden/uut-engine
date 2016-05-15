#include "PropertyInfo.h"

namespace uut
{
	PropertyInfo::PropertyInfo(const String& name, FieldAttribute attributes)
		: _name(name)
		, _attributes(attributes)
	{
	}

	MemberType PropertyInfo::GetMemberType() const
	{
		return MemberType::Property;
	}

	bool PropertyInfo::IsPublic() const
	{
		return _attributes == FieldAttribute::Public;
	}

	bool PropertyInfo::IsPrivate() const
	{
		return _attributes == FieldAttribute::Private;
	}

	bool PropertyInfo::IsStatic() const
	{
		return _attributes == FieldAttribute::Static;
	}

	const String& PropertyInfo::GetName() const
	{
		return _name;
	}
}