#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Rect.h>

namespace uut
{
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(texSize * 2);
	}

	void SampleApp::OnInit()
	{
		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
		_plasma = new Plasma(_texture->GetSize());

		_gui = new ImGuiModule(_renderer, _input);
		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_2D);

		_timer.Start();
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_timer.Update();
		_gui->NewFrame();

		///////////////////////////////////////////////////////////////
		{
			static float f = 0.0f;
			_gui->Label("Hello, world!");
			f = _gui->FloatSlider(f, 0, 1);
			if (_gui->Button("Test Window"))
				show_test_window ^= 1;
		}

// 		if (show_test_window)
// 		{
// 			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
// 			ImGui::ShowTestWindow(&show_test_window);
// 		}

		///////////////////////////////////////////////////////////////
		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_plasma->Apply(_texture,
				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));

			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			_renderer->EndScene();
		}
	}
}

int main(int argc, char *argv[])
{
	uut::SampleApp app;
	app.Run();

	return 0;
}