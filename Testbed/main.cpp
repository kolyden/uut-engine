#include "main.h"
#include <Windows.h>
#include "TestTilemap.h"
#include <Core/Time.h>

namespace uut
{
	TestbedApp::TestbedApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void TestbedApp::OnInit()
	{
		Context::RegisterModule(new Graphics());
		Context::RegisterModule(new DebugGUI());

		_graphics->SetProjection(Graphics::PM_2D);
		_currentTest = new TestTilemap();
	}

	void TestbedApp::OnFrame()
	{
		_gui->NewFrame();
		static ModuleInstance<Renderer> renderer;

		if (_currentTest)
			_currentTest->Update(Time::GetDeltaTime());

		renderer->Clear(Color32(114, 144, 154));
		if (renderer->BeginScene())
		{
			if (_currentTest)
				_currentTest->Render();
			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			renderer->EndScene();
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