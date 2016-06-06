#include "main.h"
#include <Windows.h>

namespace uut
{
	TestbedApp::TestbedApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void TestbedApp::OnInit()
	{
		_gui = new DebugGUI();
		_graphics = new Graphics();
		_graphics->SetProjection(Graphics::PM_2D);
	}

	void TestbedApp::OnFrame()
	{
		_gui->NewFrame();

		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			_renderer->EndScene();
		}
	}
}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
{
	uut::TestbedApp app;
	app.Run();

	return 0;
}