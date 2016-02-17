#include "main.h"
#include <Core/Math/Math.h>
#include "Core/Video/VertexBuffer.h"
#include "Core/Video/IndexBuffer.h"

namespace uut
{
	struct Vertex
	{
		float x, y, z;
		uint32_t color;
		float tx, ty;
	};

	static const Vertex g_verts[] = {

// 		{ 10.0f, 400.0f, 5.0f, 0xFFFFFFFF, 0.0f, 0.0f },
// 		{ 400.0f, 400.0f, 5.0f, 0xFF0000FF, 1.0f, 1.0f },
// 		{ 400.0f, 10.0f, 5.0f, 0xFFFF0000, 1.0f, 0.0f },
// 		{ 10.0f, 10.0f, 5.0f, 0xFF00FF00, 0.0f, 1.0f },

		{ 10.0f, 400.0f, 5.0f, 0xFFFFFFFF, 0.0f, 0.0f },
		{ 400.0f, 400.0f, 5.0f, 0xFFFFFFFF, 1.0f, 0.0f },
		{ 400.0f, 10.0f, 5.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{ 10.0f, 10.0f, 5.0f, 0xFFFFFFFF, 0.0f, 1.0f },

	};

	static const uint16_t g_indeces[] = {
		0, 1, 2,
		3, 0, 2,
	};

	static const VertexElement g_declare[] = {
		VertexElement(VertexElement::DT_FLOAT3, VertexElement::UT_POSITION),
		VertexElement(VertexElement::DT_COLOR, VertexElement::UT_COLOR, sizeof(float) * 3),
		VertexElement(VertexElement::DT_FLOAT2, VertexElement::UT_TEXCOORD, sizeof(float) * 3 + 4),
	};

	SampleApp::SampleApp()
	{
		_windowSize = IntVector2(texSize * 2);
	}

	void SampleApp::OnInit()
	{
		for (int i = 0; i < 256; i++)
		{
			const int r = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 32));
			const int g = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 64));
			const int b = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 128));
			_palette[i] = Color32(Math::Clamp(r, 0, 255), Math::Clamp(g, 0, 255), Math::Clamp(b, 0, 255)).ToInt();
		}

		for (int y = 0; y < texSize; y++)
		for (int x = 0; x < texSize; x++)
		{
			const int color = int(
				128.0f + (128.0f*sinf(x / 16.0f)) +
				128.0f + (128.0f*sinf(y / 16.0f)));
			_plasma[x + y*texSize] = color;
		}

		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);

		_vb = _renderer->CreateVertexBuffer(sizeof(Vertex) * 4);
		if (_vb) _vb->UpdateData(g_verts, _vb->GetSize());

		_ib = _renderer->CreateIndexBuffer(sizeof(uint16_t) * 6);
		if (_ib) _ib->UpdateData(g_indeces, _vb->GetSize());

		_vd = _renderer->CreateVertexDeclaration(g_declare, 3);

		_timer.Start();
	}

	void SampleApp::OnFrame()
	{
		_timer.Update();
		_renderer->ResetStates();
		_renderer->Clear(Color::WHITE);
		if (_renderer->BeginScene())
		{
			if (_texture)
			{
				int pitch;
				void* buf = _texture->Lock(&pitch);
				if (buf != nullptr)
				{
					const int paletteShift = Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10);

					for (int y = 0; y < texSize; y++)
					for (int x = 0; x < texSize; x++)
					{
						auto ptr = (uint32_t*)((char*)buf + x * 4 + y *pitch);
						*ptr = _palette[(_plasma[x + y*texSize] + paletteShift) % 256];
					}

					_texture->Unlock();
				}
			}

			_renderer->SetTexture(0, _texture);
			_renderer->SetVertexBuffer(_vb, sizeof(Vertex));
			_renderer->SetIndexBuffer(_ib);
			_renderer->SetVertexDeclaration(_vd);
// 			_renderer->DrawPrimitive(Topology::TrinagleList, 1);
			_renderer->DrawIndexedPrimitive(Topology::TrinagleList, 0, 0, 4, 0, 2);

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