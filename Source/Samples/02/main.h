#pragma once
#include "Core/Windows/Application.h"
#include "Core/GUI/ImGuiModule.h"
#include <Core/Video/Graphics.h>
#include <Core/Video/Camera.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		SharedPtr<Camera> _camera;
		SharedPtr<Graphics> _graphics;
		SharedPtr<ImGuiModule> _gui;
		Timer _timer;
		Vector3 _position;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}