#include "Char.h"
#include "Reflection/ConverterInfo.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Char)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(int);
		UUT_REGISTER_CONVERTER_DEFAULT(unsigned);
// 		UUT_REGISTER_CONVERTER_DEFAULT(wchar_t);
	}
}