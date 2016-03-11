#pragma once
#include "Core/Windows/Application.h"
#include "Core/GUI/ImGuiModule.h"
#include <Core/Video/Graphics.h>
#include <Core/Video/FreeCamera.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	class Plasma;
	class ResourceLoader;

	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		SharedPtr<FreeCamera> _camera;
		SharedPtr<Graphics> _graphics;
		SharedPtr<ImGuiModule> _gui;
		SharedPtr<Texture2D> _tex0;
		SharedPtr<Texture2D> _tex1;
		SharedPtr<Plasma> _plasma;
		SharedPtr<ResourceLoader> _texLoader;
		Timer _timer;
		int _frameCounter;
		float _frameTimer;
		int _fpsCount;

		bool _dragStart;
		IntVector2 _dragPos;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}