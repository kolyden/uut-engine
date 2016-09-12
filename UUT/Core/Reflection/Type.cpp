#include "Type.h"
#include <Core/Context.h>
#include <Core/String.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Attribute.h>
#include "ConverterInfo.h"
#include <Core/Debug.h>
#include <Core/AttributeUsage.h>
#include "ConstructorInfo.h"

namespace uut
{
	Type::Type(const char* library, const char* name, const Type* base, REGFUNC regfunc)
		: _name(name)
		, _library(library)
		, _fullname(_library + "::" + _name)
		, _hash(StringToHast(_fullname.c_str()))
		, _base(nullptr)
		, _regfunc(regfunc)
	{
		if (base != nullptr && base != this)
			_base = base;		
	}

	Type::~Type() {}

	const char* Type::GetName() const
	{
		return _name.c_str();
	}

	const char* Type::GetLibrary() const
	{
		return _library.c_str();
	}

	const char* Type::GetFullName() const
	{
		return _fullname.c_str();
	}

	size_t Type::GetHash() const
	{
		return _hash;
	}

	String Type::ToString() const
	{
		return _name;
	}

	SharedPtr<Object> Type::CreateObject() const
	{
		if (!IsDerived<Object>())
			return nullptr;

		for (auto it : _members)
		{
			if (it->GetMemberType() != MemberType::Constructor)
				continue;

			auto ctor = static_cast<const IConstructorInfo*>(it);
			if (ctor->GetArgsTypes().Count() != 0)
				continue;

			auto buf = new char[GetSize()];
			ctor->Call(buf);
			return SharedPtr<Object>(reinterpret_cast<Object*>(buf));
		}

		return nullptr;
	}

	bool Type::AddAttribute(const SharedPtr<Attribute>& attr)
	{
		if (!attr)
			return false;

		auto attrType = attr->GetType();
		auto attrUsage = attrType->FindAttribute<AttributeUsage>();
		if (attrUsage != nullptr)
		{
			// TODO: test targets

			if (!attrUsage->IsAllowMultiple() && FindAttribute(attrType) != nullptr)
			{
				Debug::LogWarning("Multiple attributes of %s not allowed", attrType->GetName());
				return false;
			}
		}

		_attributes << attr;
		return true;
	}

	const Attribute* Type::FindAttribute(const Type* type) const
	{
		if (type == nullptr)
			return nullptr;

		for (auto& attr : _attributes)
		{
			if (attr->GetType()->IsDerived(type))
				return attr;
		}

		return nullptr;
	}

	size_t Type::FindAttributes(const Type* type, List<const Attribute*>& list) const
	{
		if (type == nullptr)
			return 0;

		size_t count = 0;
		for (auto& attr : _attributes)
		{
			if (attr->GetType()->IsDerived(type))
			{
				count++;
				list << attr;
			}
		}
		return count;
	}

	List<const Attribute*> Type::FindAttributes(const Type* type) const
	{
		List<const Attribute*> list;
		FindAttributes(type, list);
		return list;
	}

	void Type::AddMember(IMemberInfo* member)
	{
		_members << member;
	}

	const List<const IMemberInfo*>& Type::GetMembers() const
	{
		return _members;
	}

	const IMemberInfo* Type::FindMember(const String& name) const
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

	List<const IPropertyInfo*> Type::GetProperties() const
	{
		List<const IPropertyInfo*> list;
		for (uint i = 0; i < _members.Count(); i++)
		{
			if (_members[i]->GetMemberType() == MemberType::Property)
				list << static_cast<const IPropertyInfo*>(_members[i]);
		}

		return list;
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

	bool Type::Convert(const ValueType& source, const Type* resultType, ValueType& result) const
	{
		if (resultType == nullptr)
			return false;

		for (const Type* type = this; type != nullptr; type = type->GetBaseType())
		{
			for (auto info : type->_members)
			{
				if (info->GetMemberType() != MemberType::Converter)
					continue;

				auto converter = static_cast<const IConverterInfo*>(info);
				if (converter->GetResultType() != resultType)
					continue;

				if (converter->Convert(source, result))
					return true;
			}
		}

		return false;
	}

	size_t Type::StringToHast(const char* str)
	{
		static std::hash<std::string> g_hashfn;
		return g_hashfn(str);
	}

	void Type::Register()
	{
		if (_regfunc != nullptr)
			_regfunc(this);
	}
}