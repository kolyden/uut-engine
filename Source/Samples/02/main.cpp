#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector3.h>
#include "Core/Video/Vertex.h"
#include <Core/Math/Random.h>
#include <Core/Math/Rect.h>

namespace uut
{
	SampleApp::SampleApp()
		: _dragStart(false)
	{
		_windowSize = IntVector2(800, 600);
	}

	void SampleApp::OnInit()
	{
		_window->SetTitle("Sample 02");
		_gui = new ImGuiModule(_renderer, _input);

		_graphics = new Graphics(_renderer);

		_camera = new FreeCamera();
		_camera->SetPosition(Vector3(0, 0, -20));

		_timer.Start();

		const Vector2 size = _renderer->GetScreenSize();
		_matProj = Matrix4::PerspectiveFov(Math::PI / 4, size.x / size.y, 0.1f, 1000.0f);
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_gui->NewFrame();
		_timer.Update();

		///////////////////////////////////////////////////////////////
		{
			ImGui::Begin("Test");
			static float f = 0.0f;
			ImGui::Text("Hello, world!");
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			if (ImGui::Button("Test Window")) show_test_window ^= 1;
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
				1000.0f / ImGui::GetIO().Framerate,
				ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(200, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		const float moveSpeed = 50.0f;
		const Radian rotateSpeed = Math::PI / 2;

		if (_input->IsKey(SDL_SCANCODE_A))
			_camera->MoveRight(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_D))
			_camera->MoveRight(+moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_S))
			_camera->MoveForward(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_W))
			_camera->MoveForward(+moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_Q))
			_camera->MoveUp(-moveSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_E))
			_camera->MoveUp(+moveSpeed * _timer.GetDeltaTime());

		if (_input->IsKey(SDL_SCANCODE_LEFT))
			_camera->Yaw(-rotateSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_RIGHT))
			_camera->Yaw(rotateSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_UP))
			_camera->Pitch(rotateSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_DOWN))
			_camera->Pitch(rotateSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_Z))
			_camera->Roll(rotateSpeed * _timer.GetDeltaTime());
		if (_input->IsKey(SDL_SCANCODE_X))
			_camera->Roll(rotateSpeed * _timer.GetDeltaTime());

		if (_input->IsMouseButton(0) && !ImGui::IsMouseHoveringAnyWindow())
		{
			if (_dragStart)
			{
				const Degree dragMove(0.1f);

				auto& curPos = _input->GetMousePos();
				const auto delta = curPos - _dragPos;
				_dragPos = curPos;

				if (delta.x != 0)
					_camera->Yaw(dragMove*delta.x);
				if (delta.y != 0)
					_camera->Pitch(dragMove*delta.y);
			}
			else
			{
				_dragStart = true;
				_dragPos = _input->GetMousePos();
			}
		}
		else _dragStart = false;

		///////////////////////////////////////////////////////////////
		_renderer->ResetStates();
		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_renderer->SetTransform(RT_PROJECTION, _matProj);
			_camera->Setup(_renderer);

			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_X * 1000, Color32::RED);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Y * 1000, Color32::GREEN);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Z * 1000, Color32::BLUE);

			_graphics->DrawSolidCube(Vector3::ZERO, 5);
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