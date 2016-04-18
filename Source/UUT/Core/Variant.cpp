#include "Variant.h"
#include "Object.h"

namespace uut
{
	Variant::Variant()
		: _type(VariantType::Empty)
	{
	}

	Variant::Variant(const Variant& other)
		: _type(other._type)
	{
		switch (other._type)
		{
		case VariantType::String:
			new (&_str) String(other._str);
			break;

		case VariantType::List:
			new (&_list) List<Variant>(other._list);
			break;

		case VariantType::Object:
			new (&_shared) SharedPtr<Object>(other._shared);
			break;
		}
	}

	Variant::Variant(bool value)
		: _type(VariantType::Boolean)
		, _bool(value)
	{
	}

	Variant::Variant(int value)
		: _type(VariantType::Integer)
		, _int(value)
	{
	}

	Variant::Variant(float value)
		: _type(VariantType::Real)
		, _real(value)
	{
	}

	Variant::Variant(const String& value)
		: _type(VariantType::String)
		, _str(value)
	{
	}

	Variant::Variant(const List<Variant>& value)
		: _type(VariantType::List)
		, _list(value)
	{
	}

	Variant::Variant(Object* object)
		: _type(VariantType::Object)
		, _shared(object)
	{
	}

	Variant::~Variant()
	{
		Clear();
	}

	void Variant::Clear()
	{
		switch (_type)
		{
		case VariantType::String:
			_str.~String();
			break;

		case VariantType::List:
			_list.~List<Variant>();
			break;

		case VariantType::Object:
			_shared.~SharedPtr<Object>();
			break;
		}
		_type = VariantType::Empty;
	}

	Variant& Variant::operator=(const Variant& other)
	{
		if (&other != this)
		{
			Clear();

			_type = other._type;
			switch (_type)
			{
			case VariantType::String:
				new (&_str) String(other._str);
				break;

			case VariantType::List:
				new (&_list) List<Variant>(other._list);
				break;

			case VariantType::Object:
				new (&_shared) SharedPtr<Object>(other._shared);
				break;
			}
		}

		return *this;
	}
}