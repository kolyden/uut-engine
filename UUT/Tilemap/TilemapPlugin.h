#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class TilemapPlugin : public Plugin
	{
	protected:
		TilemapPlugin();

		void OnRegister() override;
	};
}