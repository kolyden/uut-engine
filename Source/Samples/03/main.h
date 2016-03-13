#pragma once
#include <Core/Windows/Application.h>
#include <Core/Video/Graphics.h>
#include <Core/Video/FreeCamera.h>
#include <Core/Timer.h>
#include <Core/Math/Plane.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	class Entity;
	class Level;
	class ResourceLoader;

	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		SharedPtr<FreeCamera> _camera;
		SharedPtr<Graphics> _graphics;
		SharedPtr<Level> _level;
		SharedPtr<Entity> _player;
		Plane _ground;
		IntVector2 _cellIndex;

		Timer _timer;
		bool _dragStart;
		IntVector2 _dragPos;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}