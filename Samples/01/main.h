#pragma once
#include <Core/Windows/Application.h>
#include <GUI/DebugGUI.h>
#include <Video/Graphics.h>

#pragma comment(lib, "SDL2/SDL2.lib")

namespace uut
{
	class Tilemap;
	class Player;

	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		static const int texSize = 402;

		SharedPtr<DebugGUI> _gui;
		SharedPtr<Graphics> _graphics;
		SharedPtr<Font> _font;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}