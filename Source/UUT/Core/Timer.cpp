#include "Timer.h"

namespace uut
{
	Timer::Timer()
	{
	}

	void Timer::Start()
	{
		_prevTime = SDL_GetTicks();
		_elapsedTime = 0;
		_deltaTime = 0;
	}

	void Timer::Update()
	{
		const uint32_t curTime = SDL_GetTicks();
		_deltaTime = 0.001f * (curTime - _prevTime);
		_elapsedTime += _deltaTime;
	}

}