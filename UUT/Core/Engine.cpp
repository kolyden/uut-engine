#include "Engine.h"
#include "Time.h"
#include "Context.h"
#include "CorePlugin.h"
#include "Video/VideoPlugin.h"
#include "Video/DX9/DX9Plugin.h"

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
		Context::AddPlugin(new CorePlugin());
		Context::AddPlugin(new VideoPlugin());
		Context::AddPlugin(new DX9Plugin());

		Context::Init();

		Time::Initialize();
		return true;
	}

	void Engine::RunFrame()
	{
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT:
				_exiting = true;
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