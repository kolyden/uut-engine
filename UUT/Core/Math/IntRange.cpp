#include "IntRange.h"
#include "Random.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(IntRange)
	{}

	int IntRange::GetRandomValue() const
	{
		return Random::Range(min, max + 1);
	}

	const IntRange IntRange::Zero;
}