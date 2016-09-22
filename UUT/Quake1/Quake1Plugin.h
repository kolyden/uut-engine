#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class Quake1Plugin : public Plugin
	{
	public:
		Quake1Plugin();

	protected:
		void OnRegister() override;
	};
}