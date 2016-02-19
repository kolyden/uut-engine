#pragma once
#include <Core/Engine.h>
#include "Core/Windows/Window.h"
#include <Core/Video/Renderer.h>
#include <Core/IO/Input.h>

namespace uut
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	protected:
		SharedPtr<Engine> _engine;
		SharedPtr<Window> _window;
		SharedPtr<Renderer> _renderer;
		SharedPtr<Input> _input;
		IntVector2 _windowSize;

		virtual void OnInit() {}
		virtual void OnFrame() {}
	};
}
