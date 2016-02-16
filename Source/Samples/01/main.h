#pragma once
#include "Core/Windows/Application.h"
#include "Core/Video/Texture.h"
#include "Core/Timer.h"

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

		SharedPtr<Texture> _texture;
		Timer _timer;
		uint32_t _palette[256];
		int _plasma[texSize*texSize];

		virtual void OnInit() override;
		virtual void OnFrame() override;
	};
}