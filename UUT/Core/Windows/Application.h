#pragma once
#include <Core/Engine.h>
#include <Core/Windows/Window.h>
#include <Core/IO/Input.h>
#include <Video/Renderer.h>
#include <Resources/ResourceCache.h>

namespace uut
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		int GetFPS() const { return _applicationFPS; }

	protected:
		SharedPtr<Engine> _engine;
		SharedPtr<Window> _window;
		IntVector2 _windowSize;

		virtual void OnInit() {}
		virtual void OnFrame() {}

	private:
		int _applicationFPS;
	};
}
