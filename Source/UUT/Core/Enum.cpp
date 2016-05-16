#include "Enum.h"
#include <Core/Reflection/Type.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_TYPE_IMPLEMENT(Enum)
	{
		UUT_REGISTER_CONVERTER_FUNC(int, GetData);
	}

	const Enum Enum::Default;

	String Enum::ToString(const Type* type) const
	{
		for (auto& it : type->GetProperties())
		{
			auto var = it->GetValue(nullptr).Get<Enum>();
			const int i = var.GetData();
			if (i == _value)
				return it->GetName();
		}

		return String::Empty;
	}
}