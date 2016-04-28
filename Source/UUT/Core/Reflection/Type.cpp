#include "Type.h"
#include <Core/Context.h>
#include <Core/Object.h>
#include <Core/ObjectFactory.h>
#include <Core/Reflection/PropertyInfo.h>

namespace uut
{
	Type::Type(TypeInfo info, const HashString& name, const Type* base, REGFUNC regfunc)
		: _name(name)
		, _base(nullptr)
		, _regfunc(regfunc)
		, _info(info)
	{
		if (base != nullptr && base != this)
			_base = base;
	}

	Type::~Type() = default;

	const HashString& Type::GetName() const
	{
		return _name;
	}

	String Type::ToString() const
	{
		return GetName().GetData();
	}

	bool Type::IsClass() const
	{
		return _info == TypeInfo::Class;
	}

	bool Type::IsMethod() const
	{
		return _info == TypeInfo::Method;
	}

	bool Type::IsEnum() const
	{
		return _info == TypeInfo::Enum;
	}

	void Type::AddMember(MemberInfo* member)
	{
		_members << member;
	}

	const List<const MemberInfo*>& Type::GetMembers() const
	{
		return _members;
	}

	List<const PropertyInfo*> Type::GetFields() const
	{
		List<const PropertyInfo*> list;
		for (uint i = 0; i < _members.Count(); i++)
		{
			if (_members[i]->GetMemberType() == MemberType::Field)
				list << static_cast<const PropertyInfo*>(_members[i]);
		}

		return list;
	}

	TypeInfo Type::GetInfo() const
	{
		return _info;
	}

	const Type* Type::GetBaseType() const
	{
		return _base;
	}

	ObjectFactory* Type::GetFactory() const
	{
		return _factory;
	}

	SharedPtr<Object> Type::Create() const
	{
		if (!_factory)
			return SharedPtr<Object>::Empty;

		return _factory->Create();
	}

	bool Type::IsDerived(const Type* from) const
	{
		return Context::IsDerived(from, this);
	}

	bool Type::CanConvert(const Type* to) const
	{
		return Context::CanConvert(this, to);
	}
}