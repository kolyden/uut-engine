#include "Application.h"
#include "Core/Video/DX9/DX9Renderer.h"

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

		_renderer = DynamicCast<Renderer>(DX9Renderer::Create(_window));
		if (_renderer == nullptr)
			return;

		_renderer->ResetStates();
		OnInit();

		while (_engine->Run())
		{
			OnFrame();
			_renderer->Present();
		}
	}
}