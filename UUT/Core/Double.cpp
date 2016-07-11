#include "Double.h"
#include "Reflection/ConverterInfo.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Double)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(float);
		UUT_REGISTER_CONVERTER_DEFAULT(int);
	}

	const Double Double::Zero(0.0);
	const Double Double::One(1.0);
	const Double Double::MaxValue(std::numeric_limits<double>::max());
	const Double Double::MinValue(std::numeric_limits<double>::min());
}