#include "Application.h"
#include "Core/Video/DX9/DX9Renderer.h"
#include <Core/Timer.h>

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
		_engine->Init();

		_window = new Window();
		_window->SetTitle("Sample 01");
		_window->SetSize(IntVector2(_windowSize));
		_window->Create();

		_input = new Input();

		_renderer = DynamicCast<Renderer>(DX9Renderer::Create(_window));
		if (_renderer == nullptr)
			return;

		_renderer->ResetStates();
		OnInit();

		Timer timer;

		static const float framePeriod = 1.0f;
		float frameTime = 0;
		int frameCount = 0;

		timer.Start();
		while (_engine->Run())
		{
			_input->UpdateState();
			OnFrame();
			_renderer->Present();

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