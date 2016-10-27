#include "Range.h"
#include "Random.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Range)
	{}

	float Range::GetRandomValue() const
	{
		return Random::Range(min, max);
	}

	const uut::Range Range::Zero;
}