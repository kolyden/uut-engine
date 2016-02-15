#include "main.h"

namespace uut
{
	static const int texSize = 256;

	static double dist(double a, double b, double c, double d)
	{
		return sqrt((a - c) * (a - c) + (b - d) * (b - d));
	}

	Application::Application()
		: _exit(false)
	{
		_window = new Window();
		_window->SetTitle("Sample 01");
		_window->SetSize(IntVector2(texSize));
		_window->Create();

		_renderer = new Renderer();
		_renderer->Create(_window);

		_texture = _renderer->CreateTexture(IntVector2(texSize), TextureAccess::Streaming);
	}

	void Application::Run()
	{
		_timer.Start();
		while (!_exit)
		{
			_window->PoolEvent();

			_timer.Update();
			_renderer->SetColor(Color32::WHITE);
			_renderer->Clear();

			void* buf = _texture->Lock();
			if (buf != nullptr)
			{
				const float time =_timer.GetElapsedTime() / 10;

				for (int y = 0; y < texSize; y++)
				for (int x = 0; x < texSize; x++)
				{
					const double value = sin(dist(time + x, y, 128.0, 128.0) / 8.0)
						+ sin(dist(x, y, 64.0, 64.0) / 8.0)
						+ sin(dist(x, time / 7 + y, 192.0, 64) / 7.0)
						+ sin(dist(x, y, 192.0, 100.0) / 8.0);
					const int color = int((4 + value)) * 32;
					((uint32_t*)buf)[x + y * texSize] = Color32(color, color * 2, 255 - color).data;
				}

				_texture->Unlock();
			}

			_renderer->DrawTexture(_texture, 0, 0);
			_renderer->Present();
		}
	}
}

int main(int argc, char *argv[])
{
	uut::SharedPtr<uut::Application> app(new uut::Application());
	app->Run();

	return 0;
}