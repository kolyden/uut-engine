#pragma once
#include <Core/Windows/Application.h>
#include <GUI/DebugGUI.h>
#include <Video/Graphics.h>
#pragma comment(lib, "SDL2/SDL2.lib")

namespace uut
{
	class BaseTest;

	class TestbedApp : public Application
	{
	public:
		TestbedApp();

	protected:
		ModuleInstance<DebugGUI> _gui;
		ModuleInstance<Graphics> _graphics;
		SharedPtr<BaseTest> _currentTest;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}