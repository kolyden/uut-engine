#include "Numeric.h"
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_NUMERIC_IMPLEMENT(Int8) {}
	UUT_NUMERIC_IMPLEMENT(UInt8) {}

	UUT_NUMERIC_IMPLEMENT(Int16)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(float);
	}

	UUT_NUMERIC_IMPLEMENT(UInt16) {}
	UUT_NUMERIC_IMPLEMENT(Int32)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(float);
		UUT_REGISTER_CONVERTER_FUNC(String, ToString);
	}
	UUT_NUMERIC_IMPLEMENT(UInt32) {}
	UUT_NUMERIC_IMPLEMENT(Int64) {}
	UUT_NUMERIC_IMPLEMENT(UInt64) {}
}