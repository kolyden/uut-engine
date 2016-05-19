#include "Random.h"
#include <random>
#include <chrono>

namespace uut
{
	static unsigned g_seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 g_generator(g_seed);

	void Random::SetSeed(unsigned seed)
	{
		g_seed = seed;
		g_generator.seed(g_seed);
	}

	unsigned Random::GetSeed()
	{
		return g_seed;
	}

	float Random::Value()
	{
		return float(g_generator()) / g_generator.max();
	}

	float Random::Range(float min, float max)
	{
		return Value() * (max - min) + min;
	}

	int Random::Range(int min, int max)
	{
		return g_generator() % (max - min + 1) + min - g_generator.min();
	}
}