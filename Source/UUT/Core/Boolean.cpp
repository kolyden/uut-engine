#include "Boolean.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(Boolean)
	{		
	}

	const Boolean Boolean::Default;
	const Boolean Boolean::True(true);
	const Boolean Boolean::False(false);

	const HashString Boolean::TrueHash("true");
	const HashString Boolean::FalseHash("false");
}