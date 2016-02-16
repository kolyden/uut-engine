#include "Application.h"

namespace uut
{
	Application::Application()
		: _windowSize(800, 600)
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

		_renderer = new Renderer();
		_renderer->Create(_window);

		OnInit();

		while (_engine->Run())
		{
			OnFrame();
			_renderer->Present();
		}
	}
}