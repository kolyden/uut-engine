#include "Single.h"
#include "Reflection/ConverterInfo.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(Single)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(double);
		UUT_REGISTER_CONVERTER_DEFAULT(int);
	}

	const Single Single::Default;
	const Single Single::Zero(0.0f);
	const Single Single::One(1.0f);
	const Single Single::MaxValue(std::numeric_limits<float>::max());
	const Single Single::MinValue(std::numeric_limits<float>::min());
}