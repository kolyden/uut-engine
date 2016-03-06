#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector3.h>
#include "Core/Video/Vertex.h"
#include <Core/Math/Random.h>
#include <Core/Math/Rect.h>

namespace uut
{
	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		_window->SetTitle("Sample 02");
		_gui = new ImGuiModule(_renderer, _input);

		_graphics = new Graphics(_renderer);

		_camera = new Camera();
		_camera->SetCameraType(CameraType::Perspective);
		_camera->SetSize(_renderer->GetScreenSize());
		_camera->SetNearClipPlane(-5);

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
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
		}

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(200, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		const float moveSpeed = 50.0f;
		const float rotateSpeed = Math::PI / 2;

		if (_input->IsKey(SDL_SCANCODE_A))
			_camera->Move(-moveSpeed * _timer.GetDeltaTime(), 0, 0);
		if (_input->IsKey(SDL_SCANCODE_D))
			_camera->Move(+moveSpeed * _timer.GetDeltaTime(), 0, 0);
		if (_input->IsKey(SDL_SCANCODE_S))
			_camera->Move(0, -moveSpeed * _timer.GetDeltaTime(), 0);
		if (_input->IsKey(SDL_SCANCODE_W))
			_camera->Move(0, +moveSpeed * _timer.GetDeltaTime(), 0);
		if (_input->IsKey(SDL_SCANCODE_Q))
			_camera->Move(0, 0, -moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_E))
			_camera->Move(0, 0, +moveSpeed * _timer.GetDeltaTime());

		if (_input->IsKey(SDL_SCANCODE_LEFT))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_X, -Radian(rotateSpeed * _timer.GetDeltaTime())));
		if (_input->IsKey(SDL_SCANCODE_RIGHT))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_X, +Radian(rotateSpeed * _timer.GetDeltaTime())));
		if (_input->IsKey(SDL_SCANCODE_UP))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_Y, -Radian(rotateSpeed * _timer.GetDeltaTime())));
		if (_input->IsKey(SDL_SCANCODE_DOWN))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_Y, +Radian(rotateSpeed * _timer.GetDeltaTime())));
		if (_input->IsKey(SDL_SCANCODE_Z))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_Z, -Radian(rotateSpeed * _timer.GetDeltaTime())));
		if (_input->IsKey(SDL_SCANCODE_X))
			_camera->Rotate(Quaternion::RotationAxis(Vector3::AXIS_Z, +Radian(rotateSpeed * _timer.GetDeltaTime())));

		///////////////////////////////////////////////////////////////
		_renderer->ResetStates();
		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_camera->Apply(_renderer);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_X * 1000, Color32::RED);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Y * 1000, Color32::GREEN);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Z * 1000, Color32::BLUE);

			_graphics->DrawTrinagle(
				Vertex(Vector3(0, 0, 0)),
				Vertex(Vector3(0, 100, 0)),
				Vertex(Vector3(100, 0, 0)));
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