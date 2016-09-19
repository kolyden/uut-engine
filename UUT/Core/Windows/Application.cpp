#include "Application.h"
#include <Core/Context.h>
#include <Core/Timer.h>
#include <Core/CorePlugin.h>
#include <Core/IO/DirectoryContainer.h>
#include <Video/DX9/DX9Renderer.h>
#include <Video/DX9/DX9Plugin.h>
#include <Video/VideoPlugin.h>
#include <SDL/SDLInput.h>

namespace uut
{
	Application::Application()
		: _windowSize(800, 600)
		, _applicationFPS(0)
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		_engine = MakeShared<Engine>();
		_engine->Initialize();

		Context::CreatePlugin<VideoPlugin>();
		Context::CreatePlugin<DX9Plugin>();

		OnRegister();

		Context::Init();

		_window = MakeShared<Window>();
		_window->SetTitle("Sample 01");
		_window->SetSize(IntVector2(_windowSize));
		_window->Create();

		Context::CreateModule<SDLInput>();
		Context::CreateModule<ResourceCache>();
		Context::AddModule(DX9Renderer::Create(_window));

		auto renderer = Context::FindModule<Renderer>();
		if (renderer == nullptr)
			return;

		auto cache = Context::FindModule<ResourceCache>();
		cache->AddContainer(MakeShared<DirectoryContainer>(""));
// 		cache->AddLoader(new Texture2DLoader());
// 		cache->AddLoader(new BitmapFontLoader());
		renderer->ResetStates();
		OnInit();

		Timer timer;

		static const float framePeriod = 1.0f;
		float frameTime = 0;
		int frameCount = 0;

		timer.Start();
		while (!_engine->IsExiting())
		{
			_engine->RunFrame();

			OnFrame();
			renderer->Present();

			timer.Update();
			frameTime += timer.GetDeltaTime();
			frameCount++;

			if (frameTime >= framePeriod)
			{
				frameTime = 0;
				_applicationFPS = frameCount;
				frameCount = 0;
			}
		}
	}
}
