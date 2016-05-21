#pragma once
#include <Core/Windows/Application.h>
#include <GUI/DebugGUI.h>
#include <Video/Graphics.h>
#pragma comment(lib, "SDL2/SDL2.lib")

namespace uut
{
	class TestbedApp : public Application
	{
	public:
		TestbedApp();

	protected:
		static const int texSize = 402;

		SharedPtr<Texture2D> _texture;
		SharedPtr<DebugGUI> _gui;
		SharedPtr<Graphics> _graphics;

		Timer _timer;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}