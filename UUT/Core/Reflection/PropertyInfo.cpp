#include "PropertyInfo.h"

namespace uut
{
	IPropertyInfo::IPropertyInfo(const String& name, FieldAttribute attributes)
		: _name(name)
		, _attributes(attributes)
	{
	}

	MemberType IPropertyInfo::GetMemberType() const
	{
		return MemberType::Property;
	}

	bool IPropertyInfo::IsPublic() const
	{
		return _attributes == FieldAttribute::Public;
	}

	bool IPropertyInfo::IsPrivate() const
	{
		return _attributes == FieldAttribute::Private;
	}

	bool IPropertyInfo::IsStatic() const
	{
		return _attributes == FieldAttribute::Static;
	}

	const String& IPropertyInfo::GetName() const
	{
		return _name;
	}
}