#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class SDLPlugin : public Plugin
	{
	public:
		SDLPlugin();

	protected:
		void OnRegister() override;
	};
}