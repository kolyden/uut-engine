#include "Time.h"
#include <SDL2/SDL.h>

namespace uut
{
	uint32_t Time::_prevTime = 0;
	float Time::_elapsedTime = 0;
	float Time::_deltaTime = 0;

	void Time::Initialize()
	{
		_prevTime = SDL_GetTicks();
	}

	void Time::BeginFrame()
	{
		const uint32_t curTime = SDL_GetTicks();
		_deltaTime = float(curTime - _prevTime) / 1000.0f;
		_elapsedTime += _deltaTime;
		_prevTime = curTime;
	}
}