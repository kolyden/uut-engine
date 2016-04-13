#include "Type.h"
#include "Object.h"
#include "ObjectFactory.h"
#include "Context.h"

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