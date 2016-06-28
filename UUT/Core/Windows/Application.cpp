#include "Application.h"
#include <Core/Timer.h>
#include <Video/DX9/DX9Renderer.h>
#include <Video/Loaders/Texture2DLoader.h>
#include <Video/Loaders/BitmapFontLoader.h>

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
		_engine = new Engine();
		_engine->Initialize();

		_window = new Window();
		_window->SetTitle("Sample 01");
		_window->SetSize(IntVector2(_windowSize));
		_window->Create();

		Context::RegisterModule(new Input());
		Context::RegisterModule(new ResourceCache());
		Context::RegisterModule(DX9Renderer::Create(_window));

		auto input = Context::FindModule<Input>();
		auto cache = Context::FindModule<ResourceCache>();
		auto renderer = Context::FindModule<Renderer>();
		if (renderer == nullptr)
			return;

		cache->AddLoader(new Texture2DLoader());
		cache->AddLoader(new BitmapFontLoader());
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
			input->UpdateState();

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