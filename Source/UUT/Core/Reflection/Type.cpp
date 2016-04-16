#include "Type.h"
#include <Core/Context.h>
#include <Core/Object.h>
#include <Core/ObjectFactory.h>

namespace uut
{
	Type::Type(const HashString& name, const Type* base, REGFUNC regfunc)
		: _name(name)
		, _base(nullptr)
		, _regfunc(regfunc)
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

	const Type* Type::GetBase() const
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