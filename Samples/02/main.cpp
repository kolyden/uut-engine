#include "main.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector3.h>
#include <Core/Video/Vertex.h>
#include <Core/Video/Effects/Plasma.h>
#include <Core/Video/Loaders/Texture2DLoader.h>
#include <Core/IO/File.h>
#include <Core/IO/FileStream.h>

namespace uut
{
	static bool pausePlasma = false;

	SampleApp::SampleApp()
		: _frameCounter(0)
		, _frameTimer(0)
		, _fpsCount(0)
		, _dragStart(false)
	{
		_windowSize = IntVector2(1024, 768);
	}

	void SampleApp::OnInit()
	{
		_window->SetTitle("Sample 02");
		_gui = new ImGuiModule(_renderer, _input);

		_graphics = new Graphics(_renderer);
		_graphics->SetProjection(Graphics::PM_3D);

		_camera = new FreeCamera();
		_camera->SetPosition(Vector3(10, 8, -20));

		_timer.Start();

		_plasma = new Plasma(IntVector2(201, 201));
		_tex0 = _renderer->CreateTexture(_plasma->GetSize());
		_plasma->Apply(_tex0);

		_texLoader = new Texture2DLoader(_renderer);
		_tex1 = DynamicCast<Texture2D>(_texLoader->Load(File::OpenRead("brick_dark0.png")));
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		_gui->NewFrame();
		_timer.Update();

		///////////////////////////////////////////////////////////////
		{
			auto& pos = _camera->GetPosition();
			ImGui::Begin("Test");
			ImGui::Text("FPS: %d", _fpsCount);
			ImGui::Text("DrawCall: %d", _renderer->GetStatistics().drawCall);
			ImGui::Text("Pos (%.1f;%.1f;%.1f)", pos.x, pos.y, pos.z);
			ImGui::Checkbox("Pause plasma", &pausePlasma);
			ImGui::End();
		}

		if (show_test_window)
		{
			ImGui::SetNextWindowPos(ImVec2(200, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow(&show_test_window);
		}

		float moveSpeed = 50.0f;
		Radian rotateSpeed = Math::PI / 2;
		if (_input->IsKey(SDL_SCANCODE_SPACE))
		{
			moveSpeed *= 4;
			rotateSpeed *= 2;
		}

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
				Degree dragMove(0.1f);
				if (_input->IsKey(SDL_SCANCODE_SPACE))
					dragMove *= 2;

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

		if (!pausePlasma)
		{
			const float shiftSpeed = 100.0f;
			static float plasmaTime = 0.0f;

			plasmaTime += shiftSpeed * _timer.GetDeltaTime();
			_plasma->Apply(_tex0, Math::RoundToInt(plasmaTime));
		}

		const float frameDelta = 1.0f;
		_frameTimer += _timer.GetDeltaTime();
		if (_frameTimer >= frameDelta)
		{
			_fpsCount = _frameCounter;
			_frameCounter = 0;
			_frameTimer -= frameDelta;
		}

		///////////////////////////////////////////////////////////////
		if (_renderer->BeginScene())
		{
			_camera->Setup(_renderer);
			_renderer->Clear(Color32(114, 144, 154));

			_graphics->DrawQuad(
				Vertex(Vector3::ZERO, Vector2::AXIS_Y),
				Vertex(Vector3(0, 0, 100), Vector2::ZERO),
				Vertex(Vector3(100, 0, 100), Vector2::AXIS_X),
				Vertex(Vector3(100, 0, 0), Vector2::ONE), _tex0);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_X * 1000, Color32::RED);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Y * 1000, Color32::GREEN);
			_graphics->DrawLine(Vector3::ZERO, Vector3::AXIS_Z * 1000, Color32::BLUE);

			const float cubeSize = 5.0f;
			for (int i = 0; i < 10; i++)
			{
				auto tex = i % 2 == 0 ? _tex1 : _tex0;
				_graphics->DrawCube(Vector3(cubeSize / 2 + cubeSize*i, cubeSize / 2, cubeSize / 2), cubeSize, Color32::WHITE, tex);
			}

			_graphics->Flush();

			_gui->SetupCamera();
			_gui->Draw();

			_renderer->EndScene();
			_frameCounter++;
		}
	}
}

int main(int argc, char *argv[])
{
	uut::SampleApp app;
	app.Run();

	return 0;
}