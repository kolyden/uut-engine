#pragma once
#include "Core/Windows/Application.h"
#include "Core/Timer.h"
#include "Core/GUI/ImGuiModule.h"
#include "Core/Video/Effects/Plasma.h"
#include <Core/Video/Graphics.h>

#pragma comment(lib, "SDL2/SDL2.lib")
#pragma comment(lib, "SDL2/SDL2main.lib")

namespace uut
{
	class SampleApp : public Application
	{
	public:
		SampleApp();

	protected:
		static const int texSize = 402;

		SharedPtr<Texture2D> _texture;
		SharedPtr<ImGuiModule> _gui;
		SharedPtr<Plasma> _plasma;
		SharedPtr<Graphics> _graphics;

		Timer _timer;
		Matrix4 _matProj;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}