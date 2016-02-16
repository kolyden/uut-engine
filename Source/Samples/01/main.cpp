#include "main.h"
#include <Core/Math/Math.h>
#include <ctime>

namespace uut
{
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
		_timer.Start();
	}

	void SampleApp::OnFrame()
	{
		_timer.Update();

		_renderer->SetColor(Color32::WHITE);
		_renderer->Clear();

		if (_texture)
		{
			void* buf = _texture->Lock();
			if (buf != nullptr)
			{
				const int paletteShift = Math::RoundToInt(1000.0f * _timer.GetElapsedTime() / 10);

				const int count = texSize*texSize;
				for (int i = 0; i < count; i++)
					static_cast<uint32_t*>(buf)[i] = _palette[(_plasma[i] + paletteShift) % 256];

				_texture->Unlock();
			}

			_renderer->DrawTexture(_texture, 0, 0);
			_renderer->DrawTexture(_texture, texSize, 0);
			_renderer->DrawTexture(_texture, 0, texSize);
			_renderer->DrawTexture(_texture, texSize, texSize);
		}
	}
}

int main(int argc, char *argv[])
{
	uut::SampleApp app;
	app.Run();

	return 0;
}