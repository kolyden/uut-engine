#pragma once

namespace uut
{
	class Random
	{
	public:
		static void SetSeed(unsigned seed);
		static unsigned GetSeed();

		static float Value();

		static float Range(float min, float max);
		static int Range(int min, int max);

	private:
		Random() = delete;
	};
}