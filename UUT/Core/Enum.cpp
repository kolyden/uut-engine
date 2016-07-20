#include "Enum.h"
#include <Core/Reflection/Type.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(EnumValue)
	{
		UUT_REGISTER_CONVERTER_FUNC(int, GetValue);
	}

	void EnumValue::SetFlag(int value)
	{
		_value = value;
	}

	int EnumValue::GetValue() const
	{
		return _value;
	}
}