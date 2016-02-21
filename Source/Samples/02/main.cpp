#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector3.h>
#include "Core/Video/Vertex.h"
#include <Core/Math/Random.h>
#include <Core/Math/Rect.h>

namespace uut
{
	SampleApp::SampleApp()
		: _position(0)
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		_window->SetTitle("Sample 02");
		_gui = new ImGuiModule(_renderer, _input);

		_graphics = new Graphics(_renderer);

		_camera = new Camera();
		_camera->SetCameraType(CameraType::Orthogonal);
		_camera->SetSize(_renderer->GetScreenSize());
		_camera->SetNearClipPlane(0);

		_timer.Start();
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_gui->NewFrame();
		_timer.Update();

		///////////////////////////////////////////////////////////////
		{
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			if (ImGui::Button("Test Window")) show_test_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

// 		_position.z += _timer.GetDeltaTime() * Math::PI /6;
// 		_camera->SetRotation(Quaternion::FromEuler(_position));

		///////////////////////////////////////////////////////////////
		_renderer->ResetStates();
		_camera->Apply(_renderer);

		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_graphics->Flush();

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