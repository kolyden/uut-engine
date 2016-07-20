#include "MethodInfo.h"

namespace uut
{
	IMethodInfo::IMethodInfo(const String& name, MethodAttributes attributes)
		: _name(name)
		, _attributes(attributes)
	{
	}

	MemberType IMethodInfo::GetMemberType() const
	{
		return MemberType::Method;
	}

	const String& IMethodInfo::GetName() const
	{
		return _name;
	}

	bool IMethodInfo::IsPrivate() const
	{
		return _attributes.HasFlag(MethodAttribute::Private);
	}

	bool IMethodInfo::IsPublic() const
	{
		return _attributes.HasFlag(MethodAttribute::Public);
	}

	bool IMethodInfo::IsStatic() const
	{
		return _attributes.HasFlag(MethodAttribute::Static);
	}
}