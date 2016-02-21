#pragma once
#include "Core/Windows/Application.h"
#include "Core/GUI/ImGuiModule.h"
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
		SharedPtr<ImGuiModule> _gui;

		Matrix4 _matProj;

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}