#include "Rangei.h"
#include "Random.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Rangei)
	{}

	int Rangei::GetRandomValue() const
	{
		return Random::Range(min, max + 1);
	}

	const Rangei Rangei::Zero;
}