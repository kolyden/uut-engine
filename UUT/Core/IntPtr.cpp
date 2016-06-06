#include "IntPtr.h"
#include <Core/Reflection/ConstructorInfo.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_STRUCT_IMPLEMENT(IntPtr)
	{
		UUT_REGISTER_CTOR_DEFAULT();
		UUT_REGISTER_CTOR(intptr_t);
		//UUT_REGISTER_CTOR(void*);
	}

	const IntPtr IntPtr::Empty;
}