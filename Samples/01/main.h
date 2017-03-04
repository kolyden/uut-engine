#pragma once
#include <Core/Windows/Application.h>
#include <GUI/DebugGUI.h>
#include <Video/Graphics.h>

#pragma comment(lib, "SDL2/SDL2.lib")

namespace uut
{
	class Tilemap;
	class Player;
	class FreeCamera;
	class Mesh;
	class Texture2D;

	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		static const int texSize = 402;

		SharedPtr<Font> _font;
		SharedPtr<FreeCamera> _camera;
		SharedPtr<Graphics> _graphics;
		SharedPtr<Mesh> _mesh;
		SharedPtr<Texture2D> _tex;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}