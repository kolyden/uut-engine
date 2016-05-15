#include "Enum.h"
#include <Core/Reflection/Type.h>
#include <Core/Reflection/PropertyInfo.h>

namespace uut
{
	UUT_TYPE_IMPLEMENT(EnumValueBase)
	{
		
	}

	const EnumValueBase EnumValueBase::Empty;

	EnumValueBase::EnumValueBase()
		: _value(0)
	{
	}

	String EnumValueBase::ToString(const Type* type) const
	{
		for (auto& it : type->GetProperties())
		{
			auto var = it->GetValue(nullptr).Get<EnumValueBase>(Empty);
			const int i = var.GetData();
			if (i == _value)
				return it->GetName();
		}

		return String::Empty;
	}
}