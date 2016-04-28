#include "Boolean.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(Boolean)
	{		
	}

	const Boolean Boolean::True;
	const Boolean Boolean::False;

	const HashString Boolean::TrueHash("true");
	const HashString Boolean::FalseHash("false");
}