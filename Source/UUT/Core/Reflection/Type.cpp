#include "Type.h"
#include <Core/Context.h>
#include <Core/String.h>
#include <Core/Reflection/PropertyInfo.h>

namespace uut
{
	static std::hash<std::string> g_hashfn;

	Type::Type(TypeInfo info, const char* name, const Type* base, REGFUNC regfunc, size_t size)
		: _name(name)
		, _hash(g_hashfn(_name))
		, _base(nullptr)
		, _regfunc(regfunc)
		, _info(info)
		, _size(size)
	{
		if (base != nullptr && base != this)
			_base = base;
	}

	Type::~Type() {}

	const char* Type::GetName() const
	{
		return _name.c_str();
	}

	size_t Type::GetHash() const
	{
		return _hash;
	}

	String Type::ToString() const
	{
		return _name;
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

	const MemberInfo* Type::FindMember(const String& name) const
	{
		if (name.IsEmpty())
			return nullptr;

		for (uint i = 0; i < _members.Count(); i++)
		{
			if (_members[i]->GetName().Equals(name, StringComparison::OrdinalIgnoreCase))
				return _members[i];
		}

		return nullptr;
	}

	List<const PropertyInfo*> Type::GetProperties() const
	{
		List<const PropertyInfo*> list;
		for (uint i = 0; i < _members.Count(); i++)
		{
			if (_members[i]->GetMemberType() == MemberType::Property)
				list << static_cast<const PropertyInfo*>(_members[i]);
		}

		return list;
	}

	TypeInfo Type::GetInfo() const
	{
		return _info;
	}

	size_t Type::GetSize() const
	{
		return _size;
	}

	const Type* Type::GetBaseType() const
	{
		return _base;
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