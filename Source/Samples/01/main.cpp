#include "main.h"
#include <Core/Math/Math.h>
#include "Core/Video/VertexBuffer.h"
#include "Core/Video/IndexBuffer.h"
#include <Core/Math/Vector3.h>
#include "Core/Video/Vertex.h"

namespace uut
{
	struct MyVertex
	{
		Vector3 pos;
		uint32_t color;
		Vector2 tex;
	};

	static const MyVertex g_verts[] = {
		{ Vector3(10.0f, 400.0f, 5.0f), 0xFFFFFFFF, Vector2(0.0f, 0.0f) },
		{ Vector3(400.0f, 400.0f, 5.0f), 0xFFFFFFFF, Vector2(1.0f, 0.0f) },
		{ Vector3(400.0f, 10.0f, 5.0f), 0xFFFFFFFF, Vector2(1.0f, 1.0f) },
		{ Vector3(10.0f, 10.0f, 5.0f), 0xFFFFFFFF, Vector2(0.0f, 1.0f) },
	};

	static const uint16_t g_indeces[] = {
		0, 1, 2,
		3, 0, 2,
	};

	static const List<VertexElement> g_declare = {
		VertexElement(VertexElement::DT_FLOAT3, VertexElement::UT_POSITION),
		VertexElement(VertexElement::DT_COLOR32, VertexElement::UT_COLOR, offsetof(MyVertex, color)),
		VertexElement(VertexElement::DT_FLOAT2, VertexElement::UT_TEXCOORD, offsetof(MyVertex, tex)),
	};

	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(texSize * 2);
	}

	void SampleApp::OnInit()
	{
		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
		_plasma = new Plasma(_texture->GetSize());

		_vb = _renderer->CreateVertexBuffer(sizeof(MyVertex) * 4);
		if (_vb) _vb->UpdateData(g_verts, _vb->GetSize());

		_ib = _renderer->CreateIndexBuffer(sizeof(uint16_t) * 6);
		if (_ib) _ib->UpdateData(g_indeces, _vb->GetSize());

		_vd = _renderer->CreateVertexDeclaration(g_declare);

		_gui = new ImGuiModule(_renderer, _input);

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

// 			_renderer->SetTransform(RT_VIEW, Matrix4::Translation(100, 0, 0));
			_renderer->SetState(RenderState::AlphaBlend, false);
			_renderer->SetTexture(0, _texture);
			_renderer->SetVertexBuffer(_vb, sizeof(MyVertex));
			_renderer->SetIndexBuffer(_ib);
			_renderer->SetVertexDeclaration(_vd);
			_renderer->DrawIndexedPrimitive(Topology::TrinagleList, 0, 0, 4, 0, 2);

// 			_renderer->SetTransform(RT_VIEW, Matrix4::IDENTITY);
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