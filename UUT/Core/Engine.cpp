#include "Engine.h"
#include "Time.h"
#include <Core/Context.h>
#include <Core/CorePlugin.h>
#include <SDL/SDLPlugin.h>
#include <SDL/SDLInput.h>
#include <SDL2/SDL_events.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Engine)
	{}

	Engine::Engine()
		: _inited(false)
		, _exiting(false)
	{
	}

	Engine::~Engine()
	{
		DoExit();
	}

	bool Engine::Initialize()
	{
		if (_inited)
			return true;

		if (SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0)
			return false;

		_inited = true;

		Time::Initialize();

		Context::CreatePlugin<CorePlugin>();
		Context::CreatePlugin<SDLPlugin>();

		return true;
	}

	void Engine::RunFrame()
	{
		SDL_Event evt;
		auto input = SDLInput::Instance();
		if (input)
			input->NewFrame();

		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT:
				_exiting = true;
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (input != nullptr)
					input->AddEvent(evt.key, evt.type == SDL_KEYDOWN);
				break;

			case SDL_MOUSEMOTION:
				if (input != nullptr)
					input->AddEvent(evt.motion);
				break;

			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
				if (input != nullptr)
					input->AddEvent(evt.button, evt.type == SDL_MOUSEBUTTONDOWN);
				break;

			case SDL_MOUSEWHEEL:
				if (input != nullptr)
					input->AddEvent(evt.wheel);
				break;
			}
		}

		Time::BeginFrame();
	}

	void Engine::Exit()
	{
		_exiting = true;
	}

	//////////////////////////////////////////////////////////////////////////////
	void Engine::DoExit()
	{
		if (!_inited)
			return;

		_inited = false;
		SDL_Quit();
	}
}