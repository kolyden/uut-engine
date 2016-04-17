#include "Variant.h"
#include "Object.h"

namespace uut
{
	Variant::Variant()
		: _type(VariantType::Empty)
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
			_shared.~List<Variant>();
			break;

		case VariantType::Object:
			_shared.~SharedPtr<Object>();
			break;
		}
		_type = VariantType::Empty;
	}
}