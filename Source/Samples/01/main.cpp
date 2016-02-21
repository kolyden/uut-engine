#include "main.h"
#include <Core/Math/Math.h>
#include "Core/Video/VertexBuffer.h"
#include "Core/Video/IndexBuffer.h"
#include <Core/Math/Vector3.h>
#include "Core/Video/Vertex.h"
#include <Core/Math/Random.h>
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

		auto& size = _renderer->GetScreenSize();
		_matProj = Matrix4::OrthoProjection(
			0, static_cast<float>(size.x),
			0, static_cast<float>(size.y),
			0, 100);
		_timer.Start();
	}

	static bool show_test_window = false;

	void SampleApp::OnFrame()
	{
		auto& size = _renderer->GetScreenSize();

		_timer.Update();
		_gui->NewFrame();

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

		///////////////////////////////////////////////////////////////
		_renderer->ResetStates();
		_renderer->SetTransform(RT_PROJECTION, _matProj);

		_renderer->Clear(Color32(114, 144, 154));
		if (_renderer->BeginScene())
		{
			_plasma->Apply(_texture,
				Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10));

			_graphics->DrawQuad(IntRect(10, 10, texSize, texSize), 15, _texture);
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