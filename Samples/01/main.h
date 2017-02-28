#pragma once
#include <Core/Windows/Application.h>
#include <GUI/DebugGUI.h>
#include <Video/Graphics.h>

#pragma comment(lib, "SDL2/SDL2.lib")

namespace uut
{
	class EntityPool;
	class Tilemap;
	class Player;
	class FreeCamera;
	class Quake1Model;
	class BSPLevel;

	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		static const int texSize = 402;

		SharedPtr<Font> _font;
		SharedPtr<FreeCamera> _camera;
		SharedPtr<Quake1Model> _model;
		SharedPtr<BSPLevel> _level;
		SharedPtr<Graphics> _opaque;
		SharedPtr<Graphics> _transparent;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}