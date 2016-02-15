#pragma once
#include "Core/Windows/Window.h"
#include "Core/Video/Renderer.h"
#include "Core/Video/Texture.h"
#include "Core/Timer.h"

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	class Application : public Object
	{
	public:
		Application();

		void Run();

	protected:
		bool _exit;
		SharedPtr<Window> _window;
		SharedPtr<Renderer> _renderer;
		SharedPtr<Texture> _texture;
		Timer _timer;
	};
}