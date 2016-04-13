#include "Engine.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Engine)
	{}

	Engine::Engine()
		: _inited(false)
		, _quited(false)
	{
	}

	Engine::~Engine()
	{
		Done();
	}

	bool Engine::Init()
	{
		if (_inited)
			return true;

		if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0)
			return false;

		_inited = true;
		return true;
	}

	void Engine::Done()
	{
		if (!_inited)
			return;

		SDL_Quit();
		_inited = false;
	}

	bool Engine::Run()
	{
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT:
				_quited = true;
				break;
			}
		}

		return !_quited;
	}
}