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
	Type::Type(const char* typeName, const Type* base, REGFUNC regfunc)
		: _name(GetNameFromTypeid(typeName))
		, _namespace(GetNamespaceFromTypeid(typeName))
		, _fullname(CreateFullName(_namespace, _name))
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

	const char* Type::GetNamespace() const
	{
		return _namespace.c_str();
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

			auto ctor = static_cast<const ConstructorInfo*>(it);
			if (ctor->GetArgsTypes().Count() != 0)
				continue;

			auto buf = new char[GetSize()];
			ctor->Call(buf);
			auto obj = reinterpret_cast<Object*>(buf);
			return obj;
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

				auto converter = static_cast<const ConverterInfo*>(info);
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

	std::string Type::GetNameFromTypeid(const char* fullname)
	{
		const int count = strlen(fullname);
		for (int i = count - 1; i >= 0; i--)
		{
			if (fullname[i] == ':')
				return &fullname[i + 1];
		}

		return fullname;
	}

	std::string Type::GetNamespaceFromTypeid(const char* fullname)
	{
		size_t p1 = std::string::npos;
		size_t p2 = std::string::npos;

		for (size_t i = 0; fullname[i] != NULL; i++)
		{
			const char c = fullname[i];
			if (c == ' ')
				p1 = i;
			else if (c == ':')
				p2 = i;
		}

		if (p1 == std::string::npos || p2 == std::string::npos)
			return fullname;

		auto name = std::string(fullname + p1 + 1, p2 - p1);
		while ((p1 = name.find("::")) != std::string::npos)
			name.replace(p1, 2, ".");

		if (name.back() == '.')
			name.resize(name.size() - 1);

		return name;
	}


	std::string Type::CreateFullName(const std::string& namesp, const std::string& name)
	{
		if (!namesp.empty())
			return namesp + '.' + name;
		return name;
	}
}