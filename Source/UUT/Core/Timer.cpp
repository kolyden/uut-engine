#include "Timer.h"

namespace uut
{
	Timer::Timer()
		: _prevTime(0)
		, _elapsedTime(0)
		, _deltaTime(0)
	{
	}

	void Timer::Start()
	{
		_prevTime = SDL_GetTicks();
		_elapsedTime = 0.0f;
		_deltaTime = 0.0f;
	}

	void Timer::Update()
	{
		const uint32_t curTime = SDL_GetTicks();
		_deltaTime = float(curTime - _prevTime) / 1000.0f;
		_elapsedTime += _deltaTime;
		_prevTime = curTime;
	}

}